#include "fintamath/functions/arithmetic/Frac.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Frac::call(const ArgumentRefVector &argsVect) const {
  return Div()(argsVect);
}

}
