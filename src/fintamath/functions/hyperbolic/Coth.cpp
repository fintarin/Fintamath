#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Coth::call(const ArgumentsVector &argsVect) const {
  return coth(convert<Real>(argsVect.front())).toMinimalObject();
}

}
