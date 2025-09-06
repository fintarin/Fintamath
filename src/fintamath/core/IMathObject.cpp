#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IMathObject)

std::string IMathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

Shared<IMathObject> IMathObject::unwrapp() const noexcept {
  return nullptr;
}

void IMathObject::registerDefaultObject() const {
}

bool equals(const Shared<IMathObject> &lhs, const Shared<IMathObject> &rhs) noexcept {
  return lhs == rhs &&
         (!lhs || lhs->equals(lhs, rhs));
}

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
