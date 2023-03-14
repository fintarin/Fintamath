#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Asinh::call(const ArgumentsRefVector &argsVect) const {
  return asinh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
