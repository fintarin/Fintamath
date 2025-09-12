#include "fintamath/functions/other/Comma.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Comma,
  {
    .name = ",",
    .argumentClasses = {IMathObject::getClassStatic(), IMathObject::getClassStatic()},
    .returnClass = IMathObject::getClassStatic(),
    .operatorPriority = OperatorPriority::Comma,
    .isVariadic = true,
  }
)
}
