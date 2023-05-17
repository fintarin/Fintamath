#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sinh::call(const ArgumentsRefVector &argsVect) const {
  return sinh(convert<Real>(argsVect.front().get())).toMinimalObject();
}

}
