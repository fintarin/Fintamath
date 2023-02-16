#include "fintamath/functions/hyperbolic/Sinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Sinh::call(const ArgumentsVector &argsVect) const {
  return sinh(convert<Real>(argsVect.front())).toMinimalObject();
}

}
