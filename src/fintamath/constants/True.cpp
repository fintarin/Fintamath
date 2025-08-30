#include "fintamath/constants/True.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(True)

std::unique_ptr<IMathObject> True::toMinimalObject() const noexcept {
  return makeObject<Boolean>(true);
}

}
