#include "fintamath/literals/constants/ComplexInf.hpp"

#include <memory>

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FINTAMATH_CHILD_CLASS_IMPLEMENTATION(ComplexInf)

MathObjectClass ComplexInf::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

std::unique_ptr<IMathObject> ComplexInf::getValue(const bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

}
