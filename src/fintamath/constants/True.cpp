#include "fintamath/constants/True.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(True)

std::shared_ptr<const IMathObject> True::getValue() const noexcept {
  static const std::shared_ptr<const IMathObject> obj = makeObject<Boolean>(false);
  return obj;
}

}
