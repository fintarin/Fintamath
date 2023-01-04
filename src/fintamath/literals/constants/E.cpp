#include "fintamath/literals/constants/E.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr E::call() const {
  return std::make_unique<Real>(E_NUM);
}

}
