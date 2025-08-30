#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(IConstant)

std::string IConstant::getName() const noexcept {
  return std::string(getClassStatic()->getName());
}

std::string IConstant::toString() const noexcept {
  return getName();
}

}
