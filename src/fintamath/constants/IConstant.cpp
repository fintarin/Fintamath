#include "fintamath/constants/IConstant.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IConstant)

std::string IConstant::toString() const noexcept {
  return std::string(getClassStatic()->getName());
}

}
