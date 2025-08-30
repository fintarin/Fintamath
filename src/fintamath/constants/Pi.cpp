#include "fintamath/constants/Pi.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

std::shared_ptr<const IMathObject> Pi::approximateValue() const noexcept {
  return getPi().clone();
}

}
