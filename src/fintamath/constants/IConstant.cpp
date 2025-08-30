#include "fintamath/constants/IConstant.hpp"

namespace fintamath {

std::string IConstant::toString() const noexcept {
  return std::string(getClassStatic()->getName());
}

}
