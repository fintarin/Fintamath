#include "fintamath/literals/constants/NegInf.hpp"

#include <memory>

#include "fintamath/numbers/Number.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(NegInf)

MathObjectClass NegInf::getValueClass() const noexcept {
  return Number::getClassStatic();
}

std::unique_ptr<MathObject> NegInf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
