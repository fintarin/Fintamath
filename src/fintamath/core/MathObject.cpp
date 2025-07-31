#include "fintamath/core/MathObject.hpp"

namespace fintamath {

std::string MathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

void MathObject::registerDefaultObject() const {
}

std::ostream &operator<<(std::ostream &out, const MathObject &rhs) {
  return out << rhs.toString();
}

}
