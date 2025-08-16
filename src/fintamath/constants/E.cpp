#include "fintamath/constants/E.hpp"

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(E)

Shared<IMathObject> E::approximateValue() const noexcept {
  return getE().clone();
}

}
