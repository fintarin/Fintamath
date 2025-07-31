#include "fintamath/literals/constants/Inf.hpp"

#include <memory>

#include "fintamath/numbers/Number.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Inf)

MathObjectClass Inf::getValueClass() const noexcept {
  return Number::getClassStatic();
}

std::unique_ptr<MathObject> Inf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
