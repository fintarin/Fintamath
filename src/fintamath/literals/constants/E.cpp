#include "fintamath/literals/constants/E.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(E)

MathObjectClass E::getValueClass() const noexcept {
  return Real::getClassStatic();
}

std::unique_ptr<IMathObject> E::getValue(bool shouldApproximate) const noexcept {
  if (!shouldApproximate) {
    return nullptr;
  }

  return std::make_unique<Real>(getE());
}

}
