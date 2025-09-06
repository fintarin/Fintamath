#include "fintamath/constants/E.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(E)

std::unique_ptr<MathObject> E::getValue(bool shouldApproximate) const noexcept {
  if (!shouldApproximate) {
    return nullptr;
  }

  return std::make_unique<Real>(getE());
}

}
