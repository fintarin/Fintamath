#include "fintamath/literals/constants/E.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(E)

std::unique_ptr<IMathObject> E::call() const {
  return getE().clone();
}

}
