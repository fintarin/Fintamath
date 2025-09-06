#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(IMathObject)

std::string IMathObject::toString() const noexcept {
  return std::string(getClass()->getName());
}

SharedPtr<IMathObject> IMathObject::unwrapp() const noexcept {
  return {};
}

void IMathObject::registerDefaultObject() const {
}

bool equals(const SharedRef<IMathObject> &lhs, const SharedRef<IMathObject> &rhs) noexcept {
  return lhs->equals(lhs, rhs);
}

std::ostream &operator<<(std::ostream &out, const IMathObject &rhs) {
  return out << rhs.toString();
}

}
