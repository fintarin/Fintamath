#include "fintamath/literals/constants/True.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CHILD_CLASS_IMPLEMENTATION(True)

MathObjectClass True::getValueClass() const noexcept {
  return Boolean::getClassStatic();
}

std::unique_ptr<IMathObject> True::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
