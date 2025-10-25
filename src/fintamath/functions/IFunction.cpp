#include "fintamath/functions/IFunction.hpp"

#include <cassert>

#include <fmt/format.h>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/constants/Undefined.hpp"
#include "fintamath/core/Converter.hpp"
#include "fintamath/core/CoreUtils.hpp"
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

SharedRef<IFunction> IFunction::FunctionMaker::make(ArgVector inArgs) const {
  return defaultFunc.get().makeSelf(std::move(inArgs));
}

bool IFunction::FunctionMaker::doArgsMatch(ArgSpan inArgs) const noexcept {
  return IFunction::doArgsMatch(getDeclaration(), inArgs);
}

const IFunction::Declaration &IFunction::FunctionMaker::getDeclaration() const noexcept {
  return defaultFunc.get().getDeclaration();
}

MathObjectClass IFunction::FunctionMaker::getClass() const noexcept {
  return defaultFunc.get().getClass();
}

IFunction::IFunction(const Declaration &inDeclaration, ArgSpan inArgs) {
  if (!doArgsMatch(inDeclaration, inArgs)) {
    throw InvalidInputException("Invalid args"); // TODO!!!
  }
}

std::string IFunction::toString() const noexcept {
  std::string name = getDeclaration().name;
  if (name.empty()) {
    return Super::toString();
  }

  std::string outStr = std::move(name);

  for (const auto &arg : getArgs()) {
    outStr += " " + arg->toString();
  }

  return "(" + outStr + ")";
}

const IFunction::FunctionMakers *IFunction::parseFunctionMakers(const std::string &str) {
  const NameToFunctionMakersMap &nameToMakersMap = getNameToFunctionMakersMap();
  const auto iter = nameToMakersMap.find(str);
  return iter != nameToMakersMap.end() ? &iter->second : nullptr;
}

void IFunction::preSimplify(SharedRef<IMathObject> &arg) {
  constexpr auto preSimplifySelfCallback = [](const IFunction &self) -> SharedPtr<IMathObject> {
    if (self.hasUndefined()) {
      return makeShared<Undefined>();
    }
    return self.preSimplifySelf();
  };

  modify(
    arg,
    preSimplifySelfCallback,
    &preSimplify,
    [](const SharedRef<IMathObject> &) {},
    FunctionState::PreSimplify
  );
}

void IFunction::simplify(SharedRef<IMathObject> &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.simplifySelf(); },
    &simplify,
    &preSimplify,
    FunctionState::Simplify
  );
}

void IFunction::solve(SharedRef<IMathObject> &arg) {
  modify(
    arg,
    [](const IFunction &func) { return func.solveSelf(); },
    &solve,
    &simplify,
    FunctionState::Solve
  );
}

void IFunction::approximate(SharedRef<IMathObject> &arg) {
  if (const auto constant = cast<IConstant>(arg)) {
    if (auto res = constant->approximateValue()) {
      arg = std::move(res).toRef();
    }
    return;
  }

  if (auto real = convert<Real>(arg)) {
    arg = std::move(real).toRef();
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

SharedPtr<IMathObject> IFunction::preSimplifySelf() const {
  return nullptr;
}

SharedPtr<IMathObject> IFunction::simplifySelf() const {
  return nullptr;
}

SharedPtr<IMathObject> IFunction::solveSelf() const {
  return nullptr;
}

SharedPtr<IMathObject> IFunction::approximateSelf() const {
  return nullptr;
}

bool IFunction::equals(const SharedRef<IMathObject> & /*self*/, const SharedRef<IMathObject> &rhs) const noexcept {
  using detail::areContainersEqual;
  using fintamath::equals;

  if (const auto rhsFunc = cast<IFunction>(rhs)) {
    return getClass() == rhsFunc->getClass() && areContainersEqual(getArgs(), rhsFunc->getArgs(), &equals);
  }

  return false;
}

void IFunction::registerDefaultObject() const {
  const Declaration &decl = getDeclaration();

  assert(!decl.name.empty() && decl.returnClass && !decl.argClasses.empty());

  detail::Tokenizer::registerToken(decl.name);

  FunctionMakers &makers = getNameToFunctionMakersMap()[decl.name];
  makers.emplace_back(castChecked<IFunction>(getDefaultObject()));
}

bool IFunction::hasUndefined() const noexcept {
  const auto args = getArgs();
  return std::ranges::find_if(
           args,
           [](const auto &selfArg) {
             return is<Undefined>(selfArg);
           }
         ) != args.end();
}

bool IFunction::doArgsMatch(const Declaration &decl, const ArgSpan &args) noexcept {
  return decl.isVariadic ? doArgsMatchVariadic(decl, args)
                         : doArgsMatchNonVariadic(decl, args);
}

bool IFunction::doArgsMatchNonVariadic(const Declaration &decl, const ArgSpan &args) noexcept {
  if (decl.argClasses.size() != args.size()) {
    return false;
  }

  for (size_t i = 0; i < args.size(); i++) {
    if (!doesArgMatch(decl.argClasses[i], args[i])) {
      return false;
    }
  }

  return true;
}

bool IFunction::doArgsMatchVariadic(const Declaration &decl, const ArgSpan &args) noexcept {
  if (args.empty()) {
    return false;
  }

  return std::ranges::all_of(args, [&decl](const SharedRef<IMathObject> &arg) {
    return std::ranges::all_of(decl.argClasses, [&arg](MathObjectClass expectedClass) {
      return doesArgMatch(expectedClass, arg);
    });
  });
}

bool IFunction::doesArgMatch(MathObjectClass expectedClass, const SharedRef<IMathObject> &arg) noexcept {
  const MathObjectClass argClass = arg->getClass();

  if (is(expectedClass, argClass) || is<Variable>(argClass)) {
    return true;
  }

  if (auto constant = cast<IConstant>(arg)) {
    return is(expectedClass, constant->getValueClass());
  }

  if (auto func = cast<IFunction>(arg)) {
    return is(expectedClass, func->getDeclaration().returnClass);
  }

  return false;
}

IFunction::NameToFunctionMakersMap &IFunction::getNameToFunctionMakersMap() {
  static NameToFunctionMakersMap nameToFunctionMakerMap;
  return nameToFunctionMakerMap;
}

}
