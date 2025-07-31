#include "fintamath/constants/False.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

std::unique_ptr<IMathObject> False::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
