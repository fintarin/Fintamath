#include "fintamath/functions/trigonometry/Cosh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cosh::call(const ArgumentsVector &argsVect) const {
  return cosh(convert<Real>(argsVect.front())).simplify();
}

}
