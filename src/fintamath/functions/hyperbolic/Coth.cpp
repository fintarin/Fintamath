#include "fintamath/functions/hyperbolic/Coth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Coth::call(const ArgumentsVector &argsVect) const {
  return coth(convert<Real>(argsVect.front())).simplify();
}

}
