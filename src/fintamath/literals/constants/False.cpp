#include "fintamath/literals/constants/False.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

MathObjectClass False::getValueClass() const noexcept {
  return Boolean::getClassStatic();
}

std::unique_ptr<MathObject> False::getValue(const bool /*shouldApproximate*/) const noexcept {
  return std::make_unique<Boolean>(false);
}

}
