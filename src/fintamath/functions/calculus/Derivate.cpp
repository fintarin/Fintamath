#include "fintamath/functions/calculus/Derivative.hpp"

#include "fintamath/expressions/DerivativeExpression.hpp"

namespace fintamath {

MathObjectPtr Derivative::call(const ArgumentsVector &argsVect) const {
  return DerivativeExpression(argsVect.at(0).get()).simplify();
}

}
