#include "fintamath/functions/hyperbolic/Cosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Cosh::call(const ArgumentsRefVector &argsVect) const {
  return cosh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
