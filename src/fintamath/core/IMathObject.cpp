#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IMathObject)

std::string IMathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

std::unique_ptr<IMathObject> IMathObject::toMinimalObject() const noexcept {
  return nullptr;
}

void IMathObject::registerDefaultObject() const {
}

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
