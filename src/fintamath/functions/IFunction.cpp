#include "fintamath/functions/IFunction.hpp"

#include <cassert>

#include <fmt/core.h>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Converter.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Tokenizer.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/numbers/Real.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {

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

void IFunction::preSimplify(Argument &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.preSimplifySelf(); },
    &preSimplify,
    [](Argument &) {},
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
    FunctionState::Solve
  );
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
  const Declaration &decl = getDeclaration();
  validateArgumentsNonNull(inArgs);
  args = unwrappArguments(std::move(inArgs));
  validateArgumentsMatch(decl, args);
  args = compressArguments(decl, getClass(), std::move(args));
}

void IFunction::validateArgumentsNonNull(const Arguments &args) {
  for (size_t i = 0; i < args.size(); i++) {
    if (!args[i]) {
      throw InvalidInputException(fmt::format(R"(Argument #{} is a null)", i));
    }
  }
}

void IFunction::validateArgumentsMatch(const Declaration &decl, const Arguments &args) {
  if (!doArgumentsMatch(decl, args)) {
    throw InvalidInputException("Invalid args"); // TODO
  }
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

  for (const auto &inArg : args) {
    bool matchAny = false;
    for (const auto &declArgClass : decl.argumentClasses) {
      if (doesArgumentMatch(declArgClass, inArg)) {
        matchAny = true;
        break;
      }
    }

    if (!matchAny) {
      return false;
    }
  }

  return true;
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

IFunction::Arguments IFunction::compressArguments(const Declaration &decl, const MathObjectClass funcClass, Arguments args) noexcept {
  if (!decl.isVariadic) {
    return args;
  }

  Arguments outArgs;
  outArgs.reserve(args.size());

  for (auto &arg : args) {
    if (arg->getClass() == funcClass) {
      const auto &argFunc = cast<IFunction>(*arg);
      const Arguments &innerArgs = argFunc.getArguments();
      outArgs.insert(outArgs.end(), innerArgs.begin(), innerArgs.end());
    }
    else {
      outArgs.emplace_back(std::move(arg));
    }
  }

  return outArgs;
}

void IFunction::modify(Argument &arg, const ModifySelfCallback &modifySelf, const ModifyCallback &modify, const ModifyCallback &prevModify, FunctionState stateAfterModify) {
  auto func = cast<IFunction>(arg);
  if (!func || func->state >= stateAfterModify) {
    return;
  }

  prevModify(arg);

  if (arg != func) {
    func = cast<IFunction>(arg);
  }

  if (!func) {
    return;
  }

  modifyArguments(func, modify);
  arg = func;

  if (auto res = modifySelf(*func)) {
    modify(res);
    arg = res;
  }
  else {
    func->state = stateAfterModify;
  }
}

void IFunction::modifyArguments(Shared<IFunction> &func, const ModifyCallback &modify) {
  const Arguments &oldArgs = func->getArguments();
  Arguments newArgs;
  size_t argIndex = 0;
  bool wasModify = false;

  for (; argIndex < oldArgs.size(); argIndex++) {
    const Argument &oldArg = oldArgs[argIndex];
    Argument newArg = oldArg;
    modify(newArg);

    if (newArg != oldArg) {
      newArgs = oldArgs;
      newArgs[argIndex] = oldArg;
      wasModify = true;
      break;
    }
  }

  if (!wasModify) {
    return;
  }

  argIndex++;

  for (; argIndex < newArgs.size(); argIndex++) {
    modify(newArgs[argIndex]);
  }

  func = func->makeSelf(std::move(newArgs));
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
