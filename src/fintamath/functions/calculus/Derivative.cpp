#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

MathObjectPtr Derivative::call(const ArgumentsVector &argsVect) const {
  return buildFunctionExpression(*this, argsVect);
}

}
