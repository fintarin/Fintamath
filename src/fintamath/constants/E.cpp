#include "fintamath/constants/E.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(E)

std::unique_ptr<IMathObject> E::approximate() const noexcept {
  return getE().clone();
}

}
