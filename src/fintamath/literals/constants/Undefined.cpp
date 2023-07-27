#include "fintamath/literals/constants/Undefined.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Undefined::call() const {
  return clone();
}

}
