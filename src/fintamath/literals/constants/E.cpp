#include "fintamath/literals/constants/E.hpp"

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> E::call() const {
  return getE().clone();
}

}
