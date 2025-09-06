#include "fintamath/constants/Pi.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

SharedPtr<IMathObject> Pi::approximateValue() const noexcept {
  return getPi().clone();
}

}
