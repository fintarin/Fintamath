#include "fintamath/literals/constants/Undefined.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CHILD_CLASS_IMPLEMENTATION(Undefined)

MathObjectClass Undefined::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

std::unique_ptr<IMathObject> Undefined::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
