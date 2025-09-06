#include "fintamath/literals/constants/NegInf.hpp"

#include <memory>

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(NegInf)

MathObjectClass NegInf::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

std::unique_ptr<IMathObject> NegInf::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
