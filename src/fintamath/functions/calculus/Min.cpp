#include "fintamath/functions/calculus/Min.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION(
  Min,
  {
    .name = "min",
    .argClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
    .isVariadic = true,
  }
)

}
