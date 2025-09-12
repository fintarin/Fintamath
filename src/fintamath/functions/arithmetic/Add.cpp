#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Add,
  {
    .name = "+",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .operatorDeclaration = OperatorDeclaration{
      .priority = OperatorPriority::Addition,
      .isAssociative = true,
    },
    .isVariadic = true,
  }
)

}
