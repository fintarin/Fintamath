#include "fintamath/literals/constants/Inf.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Inf::call() const {
  return clone();
}

}
