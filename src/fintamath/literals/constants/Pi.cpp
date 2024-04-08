#include "fintamath/literals/constants/Pi.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Pi)

std::unique_ptr<IMathObject> Pi::call() const {
  return getPi().clone();
}

}
