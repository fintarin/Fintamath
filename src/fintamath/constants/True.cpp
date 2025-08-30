#include "fintamath/constants/True.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(True)

std::unique_ptr<MathObject> True::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
