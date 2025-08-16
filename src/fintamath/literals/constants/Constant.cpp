#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {

std::unique_ptr<MathObject> Constant::getValue(bool /*shouldApproximate*/) const noexcept {
  return nullptr;
}

std::string Constant::toString() const noexcept {
  return std::string(getClassStatic()->getName());
}

}
