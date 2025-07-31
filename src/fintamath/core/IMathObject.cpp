#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(IMathObject)

std::string IMathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
