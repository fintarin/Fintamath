#include "fintamath/constants/True.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(True)

Shared<IMathObject> True::getValue() const noexcept {
  static const auto obj = makeShared<Boolean>(true);
  return obj;
}

}
