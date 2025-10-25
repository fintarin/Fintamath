#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Mul,
  {
    .name = "*",
    .argClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorDeclaration = OperatorDeclaration{
      .priority = OperatorPriority::Multiplication,
      .isAssociative = true,
    },
    .isVariadic = true,
  }
)

}
