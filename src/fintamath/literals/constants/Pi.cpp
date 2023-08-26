#include "fintamath/literals/constants/Pi.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pi::call() const {
  return getPi().clone();
}

}
