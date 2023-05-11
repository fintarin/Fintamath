#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> E::call() const {
  return std::make_unique<Real>(getE());
}

}
