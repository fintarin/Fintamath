#include "fintamath/core/MathObjectBase.hpp"

namespace fintamath {

MathObjectClass MathObjectBase::getClass() const noexcept {
  return getClassStatic();
}

const MathObjectBase &MathObjectBase::getDefaultObject() const {
  static const MathObjectBase defaultObjectMathObjectBase;
  return defaultObjectMathObjectBase;
}

}
