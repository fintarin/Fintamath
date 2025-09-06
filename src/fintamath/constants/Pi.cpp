#include "fintamath/constants/Pi.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

std::unique_ptr<IMathObject> Pi::approximate() const noexcept {
  return getPi().clone();
}

}
