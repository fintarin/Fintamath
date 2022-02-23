#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  bool MathObject::operator==(const MathObject &rhs) const {
    return this->toString() == rhs.toString();
  }

  bool MathObject::operator!=(const MathObject &rhs) const {
    return !(*this == rhs);
  }
}