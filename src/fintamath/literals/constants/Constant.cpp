#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Constant)

MathObjectClass Constant::getValueClass() const noexcept {
  return MathObject::getClassStatic();
}

std::unique_ptr<MathObject> Constant::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

std::string Constant::getName() const noexcept {
  return std::string(getClassStatic()->getName());
}

std::string Constant::toString() const noexcept {
  return getName();
}

}
