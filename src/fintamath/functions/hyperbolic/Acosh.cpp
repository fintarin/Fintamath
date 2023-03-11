#include "fintamath/functions/hyperbolic/Acosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acosh::call(const ArgumentsVector &argsVect) const {
  return acosh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
