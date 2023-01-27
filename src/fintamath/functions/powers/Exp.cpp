#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Exp::call(const ArgumentsVector &argsVect) const {
  return exp(convert<Real>(argsVect.front())).simplify();
}

}
