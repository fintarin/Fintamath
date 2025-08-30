#include "fintamath/constants/False.hpp"

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

Shared<IMathObject> False::getValue() const noexcept {
  static const auto obj = makeShared<Boolean>(false);
  return obj;
}

}
