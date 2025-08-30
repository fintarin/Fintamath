#include "fintamath/constants/Pi.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

std::unique_ptr<MathObject> Pi::getValue(bool shouldApproximate) const noexcept {
  if (!shouldApproximate) {
    return nullptr;
  }

  return std::make_unique<Real>(getPi());
}

}
