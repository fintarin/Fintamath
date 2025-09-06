#include "fintamath/literals/constants/Pi.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

MathObjectClass Pi::getValueClass() const noexcept {
  return Real::getClassStatic();
}

std::unique_ptr<IMathObject> Pi::getValue(bool shouldApproximate) const noexcept {
  if (!shouldApproximate) {
    return nullptr;
  }

  return std::make_unique<Real>(getPi());
}

}
