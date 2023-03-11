#include "fintamath/functions/hyperbolic/Asinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Asinh::call(const ArgumentsVector &argsVect) const {
  return asinh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
