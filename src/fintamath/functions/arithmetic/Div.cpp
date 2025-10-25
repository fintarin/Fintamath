#include "fintamath/functions/arithmetic/Div.hpp"

#include <fmt/format.h>

#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Div,
  {
    .name = "/",
    .argClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorDeclaration = OperatorDeclaration{
      .priority = OperatorPriority::Exponentiation,
    },
  }
)

std::string Div::toString() const noexcept {
  using detail::argumentToString;

  const IFunction::Declaration &decl = getDeclaration();
  const std::string leftArgStr = argumentToString(decl, getArgLeft());
  const std::string rightArgStr = argumentToString(decl, getArgRight());

  return fmt::format("{}{}{}", leftArgStr, decl.name, rightArgStr);
}

}
