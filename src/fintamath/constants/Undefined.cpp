#include "fintamath/constants/Undefined.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Undefined)

std::unique_ptr<MathObject> Undefined::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
