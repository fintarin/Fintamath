#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

MathObjectPtr Derivative::call(const ArgumentsVector &argsVect) const {
  return makeFunctionExpression(*this, toArgumentsPtrVect(argsVect));
}

}
