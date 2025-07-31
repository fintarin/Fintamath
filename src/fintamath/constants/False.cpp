#include "fintamath/constants/False.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

std::shared_ptr<const IMathObject> False::getValue() const noexcept {
  static const std::shared_ptr<const IMathObject> obj = makeObject<Boolean>(false);
  return obj;
}

}
