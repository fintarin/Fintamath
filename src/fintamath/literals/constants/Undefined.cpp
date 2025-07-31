#include "fintamath/literals/constants/Undefined.hpp"

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/numbers/Number.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Undefined)

MathObjectClass Undefined::getValueClass() const noexcept {
  return Number::getClassStatic();
}

std::unique_ptr<MathObject> Undefined::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
