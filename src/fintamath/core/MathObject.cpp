#include "fintamath/core/MathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(MathObject)

std::string MathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

void MathObject::registerDefaultObject() const {
  detail::MathObjectIdStorage::add(getClass());
}

std::ostream &operator<<(std::ostream &out, const MathObject &rhs) {
  return out << rhs.toString();
}

}
