#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Mul,
  {
    .name = "*",
    .argumentClasses = {INumber::getClassStatic(), INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorPriority = OperatorPriority::Multiplication,
    .isVariadic = true,
  }
)

}
