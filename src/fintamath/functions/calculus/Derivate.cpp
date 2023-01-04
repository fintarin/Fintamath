#include "fintamath/functions/calculus/Derivate.hpp"

#include "fintamath/expressions/DerivateExpression.hpp"

namespace fintamath {

MathObjectPtr Derivate::call(const ArgumentsVector &argsVect) const {
  return DerivateExpression(argsVect.at(0).get()).simplify();
}

}
