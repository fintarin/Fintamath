#include "fintamath/core/MathObjectBase.hpp"

namespace fintamath {

MathObjectClass MathObjectBase::getClass() const noexcept {
  return getClassStatic();
}

}
