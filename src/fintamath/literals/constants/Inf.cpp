#include "fintamath/literals/constants/Inf.hpp"

#include <memory>

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CHILD_CLASS_IMPLEMENTATION(Inf)

MathObjectClass Inf::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

std::unique_ptr<IMathObject> Inf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
