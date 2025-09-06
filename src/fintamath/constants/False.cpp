#include "fintamath/constants/False.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(False)

std::unique_ptr<IMathObject> False::toMinimalObject() const noexcept {
  return makeObject<Boolean>(false);
}

}
