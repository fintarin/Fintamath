#include "fintamath/functions/IFunctionBinary.hpp"

#include <string>

#include <fmt/format.h>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IFunctionBinary)

std::string IFunctionBinary::toString() const noexcept {
  using detail::argumentToString;

  const IFunction::Declaration &decl = getDeclaration();
  const std::string leftArgStr = argumentToString(decl, getLeftArgument());
  const std::string rightArgStr = argumentToString(decl, getRightArgument());

  if (!decl.operatorDeclaration) {
    return fmt::format("{}({}, {})", decl.name, leftArgStr, rightArgStr);
  }

  return fmt::format("{} {} {}", leftArgStr, decl.name, rightArgStr);
}

const SharedRef<IMathObject> &IFunctionBinary::getLeftArgument() const {
  return getArguments()[0];
}

const SharedRef<IMathObject> &IFunctionBinary::getRightArgument() const {
  return getArguments()[1];
}

IFunctionBinary::SimplifyFunctions IFunctionBinary::getFunctionsForPreSimplify() const {
  return {};
}

IFunctionBinary::SimplifyFunctions IFunctionBinary::getFunctionsForSimplify() const {
  return {};
}

SharedPtr<IMathObject> IFunctionBinary::preSimplifySelf() const {
  using detail::useSimplifyFunctions;
  return useSimplifyFunctions(getFunctionsForPreSimplify(), getLeftArgument(), getRightArgument());
}

SharedPtr<IMathObject> IFunctionBinary::simplifySelf() const {
  using detail::useSimplifyFunctions;
  return useSimplifyFunctions(getFunctionsForSimplify(), getLeftArgument(), getRightArgument());
}

void IFunctionBinary::registerDefaultObject() const {
  Super::registerDefaultObject();

  [[maybe_unused]] const auto &decl = getDeclaration();
  assert(decl.argumentClasses.size() == 2 && !decl.isVariadic);
}

}
