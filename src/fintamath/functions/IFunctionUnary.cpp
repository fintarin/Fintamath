#include "fintamath/functions/IFunctionUnary.hpp"

#include <string>

#include <fmt/format.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunctionUnary)

std::string IFunctionUnary::toString() const noexcept {
  using detail::argumentToString;

  const Declaration &decl = getDeclaration();
  const std::string argStr = argumentToString(decl, getArgument());

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

const SharedRef<IMathObject> &IFunctionUnary::getArgument() const {
  return getArguments()[0];
}

IFunctionUnary::SimplifyFunctions IFunctionUnary::getFunctionsForPreSimplify() const {
  return {};
}

IFunctionUnary::SimplifyFunctions IFunctionUnary::getFunctionsForSimplify() const {
  return {};
}

SharedPtr<IMathObject> IFunctionUnary::preSimplifySelf() const {
  using detail::useSimplifyFunctions;
  return useSimplifyFunctions(getFunctionsForPreSimplify(), getArgument());
}

SharedPtr<IMathObject> IFunctionUnary::simplifySelf() const {
  using detail::useSimplifyFunctions;
  return useSimplifyFunctions(getFunctionsForSimplify(), getArgument());
}

void IFunctionUnary::registerDefaultObject() const {
  Super::registerDefaultObject();

  [[maybe_unused]] const auto &decl = getDeclaration();
  assert(decl.argumentClasses.size() == 1 && !decl.isVariadic);
}

}
