#include "fintamath/functions/trigonometry/Coth.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Coth::call(const ArgumentsVector &argsVect) const {
  return coth(convert<Real>(argsVect.front())).simplify();
}

}
