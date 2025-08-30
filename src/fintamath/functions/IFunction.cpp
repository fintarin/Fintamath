#include "fintamath/functions/IFunction.hpp"

#include <cassert>

#include <fmt/core.h>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Converter.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {

std::mutex IFunction::modifyStateMutex;

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunction)

IFunction::FunctionMaker::FunctionMaker(const IFunction &inDefaultFunc)
    : defaultFunc(inDefaultFunc) {
}

Shared<IFunction> IFunction::FunctionMaker::make(Arguments inArgs) const {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

bool IFunction::FunctionMaker::doArgumentsMatch(const Arguments &inArgs) const noexcept {
  return IFunction::doArgumentsMatch(getDeclaration(), inArgs);
}

const IFunction::Declaration &IFunction::FunctionMaker::getDeclaration() const noexcept {
  return defaultFunc.get().getDeclaration();
}

MathObjectClass IFunction::FunctionMaker::getClass() const noexcept {
  return defaultFunc.get().getClass();
}

std::string IFunction::toString() const noexcept {
  std::string name = getDeclaration().name;
  if (name.empty()) {
    return Super::toString();
  }

  std::string outStr = std::move(name);

  for (const auto &arg : getArguments()) {
    outStr += " " + arg->toString();
  }

  return "(" + outStr + ")";
}

Shared<IMathObject> IFunction::unwrapp() const noexcept {
  if (getDeclaration().isVariadic && args.size() == 1) {
    return args.front();
  }

  return {};
}

const IFunction::Arguments &IFunction::getArguments() const noexcept {
  return args;
}

const IFunction::FunctionMakers *IFunction::parseFunctionMakers(const std::string &str) {
  const NameToFunctionMakersMap &nameToMakersMap = getNameToFunctionMakersMap();
  const auto iter = nameToMakersMap.find(str);
  return iter != nameToMakersMap.end() ? &iter->second : nullptr;
}

void IFunction::compress(Argument &arg) {
  if (const auto func = cast<IFunction>(arg)) {
    if (auto res = func->compressSelf()) {
      arg = res;
    }
  }
}

void IFunction::preSimplify(Argument &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.preSimplifySelf(); },
    &preSimplify,
    &compress,
    FunctionState::PreSimplify
  );
}

void IFunction::simplify(Argument &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.simplifySelf(); },
    &simplify,
    &preSimplify,
    FunctionState::Simplify
  );
}

void IFunction::solve(Argument &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.solveSelf(); },
    &solve,
    &simplify,
    FunctionState::Solve
  );
}

void IFunction::approximate(Argument &arg) {
  if (const auto constant = cast<IConstant>(arg)) {
    if (auto res = constant->approximateValue()) {
      arg = res;
    }
    return;
  }

  if (auto real = convert<Real>(arg)) {
    arg = real;
    return;
  }

  modify(
    arg,
    [](const IFunction &func) { return func.approximateSelf(); },
    &approximate,
    &solve,
    FunctionState::Approximate
  );
}

Shared<IMathObject> IFunction::compressSelf() const {
  if (!getDeclaration().isVariadic) {
    return nullptr;
  }

  const MathObjectClass selfClass = getClass();
  size_t selfArgIndex = 0;
  std::optional<Arguments> outArgs;

  for (; selfArgIndex < args.size(); selfArgIndex++) {
    const Argument &arg = args[selfArgIndex];

    if (is(selfClass, arg->getClass())) {
      outArgs = Arguments(
        args.begin(),
        args.begin() + static_cast<ptrdiff_t>(selfArgIndex)
      );

      appendVariadicFunctionArguments(cast<IFunction>(*arg), selfClass, *outArgs);

      break;
    }
  }

  if (!outArgs) {
    return nullptr;
  }

  selfArgIndex++;

  for (; selfArgIndex < args.size(); selfArgIndex++) {
    appendVariadicFunctionArgument(args[selfArgIndex], selfClass, *outArgs);
  }

  return makeSelf(std::move(*outArgs));
}

Shared<IMathObject> IFunction::preSimplifySelf() const {
  return nullptr;
}

Shared<IMathObject> IFunction::simplifySelf() const {
  return nullptr;
}

Shared<IMathObject> IFunction::solveSelf() const {
  return nullptr;
}

Shared<IMathObject> IFunction::approximateSelf() const {
  return nullptr;
}

void IFunction::registerDefaultObject() const {
  const Declaration &decl = getDeclaration();

  assert(!decl.argumentClasses.empty());

  if (decl.name.empty()) {
    return;
  }

  detail::Tokenizer::registerToken(decl.name);

  FunctionMakers &makers = getNameToFunctionMakersMap()[decl.name];
  makers.emplace_back(cast<IFunction>(getDefaultObject()));
}

void IFunction::initSelf(Arguments inArgs) {
  assert(areArgumentsNonNull(inArgs));
  args = unwrappArguments(std::move(inArgs));
  assert(doArgumentsMatch(getDeclaration(), args));
}

bool IFunction::areArgumentsNonNull(const Arguments &args) {
  return std::ranges::all_of(args, [](const Argument &arg) {
    return static_cast<bool>(arg);
  });
}

bool IFunction::doArgumentsMatch(const Declaration &decl, const Arguments &args) noexcept {
  return decl.isVariadic ? doArgumentsMatchVariadic(decl, args)
                         : doArgumentsMatchNonVariadic(decl, args);
}

bool IFunction::doArgumentsMatchNonVariadic(const Declaration &decl, const Arguments &args) noexcept {
  if (decl.argumentClasses.size() != args.size()) {
    return false;
  }

  for (size_t i = 0; i < args.size(); i++) {
    if (!doesArgumentMatch(decl.argumentClasses[i], args[i])) {
      return false;
    }
  }

  return true;
}

bool IFunction::doArgumentsMatchVariadic(const Declaration &decl, const Arguments &args) noexcept {
  if (args.empty()) {
    return false;
  }

  return std::ranges::all_of(args, [&decl](const Argument &arg) {
    return std::ranges::all_of(decl.argumentClasses, [&arg](MathObjectClass expectedClass) {
      return doesArgumentMatch(expectedClass, arg);
    });
  });
}

bool IFunction::doesArgumentMatch(MathObjectClass expectedClass, const Argument &arg) noexcept {
  const MathObjectClass argClass = arg->getClass();

  if (is(expectedClass, argClass) || is<Variable>(argClass)) {
    return true;
  }

  if (is<IFunction>(argClass)) {
    const auto &func = cast<IFunction>(*arg);
    return is(expectedClass, func.getDeclaration().returnClass);
  }

  return false;
}

IFunction::Arguments IFunction::unwrappArguments(Arguments args) noexcept {
  for (auto &arg : args) {
    if (auto unwrappedArg = arg->unwrapp()) {
      arg = std::move(unwrappedArg);
    }
  }

  return args;
}

void IFunction::appendVariadicFunctionArgument(const Argument &arg, const MathObjectClass &selfClass, Arguments &outArgs) {
  if (is(selfClass, arg->getClass())) {
    appendVariadicFunctionArguments(cast<IFunction>(*arg), selfClass, outArgs);
  }
  else {
    outArgs.emplace_back(arg);
  }
}

void IFunction::appendVariadicFunctionArguments(const IFunction &func, const MathObjectClass &selfClass, Arguments &outArgs) noexcept {
  const Arguments &args = func.getArguments();

  outArgs.reserve(outArgs.size() + args.size());

  for (const auto &arg : args) {
    appendVariadicFunctionArgument(arg, selfClass, outArgs);
  }
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
