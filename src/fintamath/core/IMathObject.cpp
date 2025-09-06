#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

std::string IMathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

void IMathObject::registerDefaultObject() const {
}

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
