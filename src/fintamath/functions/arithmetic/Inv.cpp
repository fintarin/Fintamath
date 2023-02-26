#include "fintamath/functions/arithmetic/Inv.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Inv::call(const ArgumentsVector &argsVect) const {
  return inv(convert<Real>(argsVect.front())).simplify();
}

}