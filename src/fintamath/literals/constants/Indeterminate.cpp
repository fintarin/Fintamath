#include "fintamath/literals/constants/Indeterminate.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Indeterminate::call() const {
  return clone();
}

}
