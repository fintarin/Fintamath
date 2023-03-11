#include "fintamath/functions/hyperbolic/Acoth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Acoth::call(const ArgumentsVector &argsVect) const {
  return acoth(convert<Real>(argsVect.front())).toMinimalObject();
}

}
