#include "fintamath/functions/IFunctionBinary.hpp"

#include <string>

#include <fmt/format.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunctionBinary)

IFunctionBinary::IFunctionBinary() : args({makeShared<Variable>(), makeShared<Variable>()}) {}

IFunctionBinary::IFunctionBinary(const Declaration &inDeclaration, ArgSpan inArgs)
    : IFunction(inDeclaration, inArgs),
      args({unwrapp(inArgs.front()), unwrapp(inArgs.back())}) {
}

IFunctionBinary::IFunctionBinary(const Declaration &inDeclaration, Args inArgs)
    : IFunction(inDeclaration, inArgs),
      args(std::move(inArgs)) {
}

std::string IFunctionBinary::toString() const noexcept {
  using detail::argumentToString;

  const IFunction::Declaration &decl = getDeclaration();
  const std::string leftArgStr = argumentToString(decl, getArgLeft());
  const std::string rightArgStr = argumentToString(decl, getArgRight());

  if (!decl.operatorDeclaration) {
    return fmt::format("{}({}, {})", decl.name, leftArgStr, rightArgStr);
  }

  return fmt::format("{} {} {}", leftArgStr, decl.name, rightArgStr);
}

IFunctionBinary::ArgSpan IFunctionBinary::getArgs() const noexcept {
  return args;
}

const SharedRef<IMathObject> &IFunctionBinary::getArgLeft() const {
  return args[0];
}

const SharedRef<IMathObject> &IFunctionBinary::getArgRight() const {
  return args[1];
}

IFunctionBinary::ModifyFunctions IFunctionBinary::getFunctionsForPreSimplify() const {
  return {};
}

IFunctionBinary::ModifyFunctions IFunctionBinary::getFunctionsForSimplify() const {
  return {};
}

SharedPtr<IMathObject> IFunctionBinary::preSimplifySelf() const {
  using detail::useModifyFunctions;
  return useModifyFunctions(getFunctionsForPreSimplify(), getArgLeft(), getArgRight());
}

SharedPtr<IMathObject> IFunctionBinary::simplifySelf() const {
  using detail::useModifyFunctions;
  return useModifyFunctions(getFunctionsForSimplify(), getArgLeft(), getArgRight());
}

void IFunctionBinary::registerDefaultObject() const {
  Super::registerDefaultObject();

  [[maybe_unused]] const auto &decl = getDeclaration();
  assert(decl.argClasses.size() == 2 && !decl.isVariadic);
}

}
