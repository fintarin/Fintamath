#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Lb::call(const ArgumentsVector &argsVect) const {
  return lb(convert<Real>(argsVect.front())).simplify();
}

}
