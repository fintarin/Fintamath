#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(IConstant)

MathObjectClass IConstant::getValueClass() const noexcept {
  return IMathObject::getClassStatic();
}

std::unique_ptr<IMathObject> IConstant::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

std::string IConstant::getName() const noexcept {
  return std::string(getClassStatic()->getName());
}

std::string IConstant::toString() const noexcept {
  return getName();
}

}
