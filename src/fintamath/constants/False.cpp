#include "fintamath/constants/False.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

std::unique_ptr<MathObject> False::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
