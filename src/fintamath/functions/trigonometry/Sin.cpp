#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_FUNCTION_CLASS_IMPLEMENTATION_WITH_MAKE(
  Sin,
  {
    .name = "sin",
    .argumentClasses = {INumber::getClassStatic()},
    .returnClass = INumber::getClassStatic(),
  }
)

}
