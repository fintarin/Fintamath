#include "fintamath/functions/IFunctionUnary.hpp"

#include <string>

#include <fmt/format.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/variables/Variable.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunctionUnary)

IFunctionUnary::IFunctionUnary() : args({makeShared<Variable>()}) {
}

IFunctionUnary::IFunctionUnary(const Declaration &inDeclaration, Args inArgs)
    : IFunction(inDeclaration, inArgs),
      args(std::move(inArgs)) {
}

IFunctionUnary::IFunctionUnary(const Declaration &inDeclaration, ArgSpan inArgs)
    : IFunction(inDeclaration, inArgs),
      args({unwrapp(inArgs.front())}) {
}

std::string IFunctionUnary::toString() const noexcept {
  using detail::argumentToString;

  const Declaration &decl = getDeclaration();
  const std::string argStr = argumentToString(decl, getArg());

  if (!decl.operatorDeclaration) {
    return fmt::format("{}({})", decl.name, argStr);
  }

  switch (decl.operatorDeclaration->priority) {
    case OperatorPriority::PostfixUnary: {
      return fmt::format("{}{}", argStr, decl.name);
    }
    default: {
      return fmt::format("{}{}", decl.name, argStr);
    }
  }
}

IFunction::ArgSpan IFunctionUnary::getArgs() const noexcept {
  return args;
}

const SharedRef<IMathObject> &IFunctionUnary::getArg() const {
  return getArgs()[0];
}

IFunctionUnary::ModifyFunctions IFunctionUnary::getFunctionsForPreSimplify() const {
  return {};
}

IFunctionUnary::ModifyFunctions IFunctionUnary::getFunctionsForSimplify() const {
  return {};
}

SharedPtr<IMathObject> IFunctionUnary::preSimplifySelf() const {
  using detail::useModifyFunctions;
  return useModifyFunctions(getFunctionsForPreSimplify(), getArg());
}

SharedPtr<IMathObject> IFunctionUnary::simplifySelf() const {
  using detail::useModifyFunctions;
  return useModifyFunctions(getFunctionsForSimplify(), getArg());
}

void IFunctionUnary::registerDefaultObject() const {
  Super::registerDefaultObject();

  [[maybe_unused]] const auto &decl = getDeclaration();
  assert(decl.argClasses.size() == 1 && !decl.isVariadic);
}

}
