#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Derivative::call(const ArgumentsRefVector &argsVect) const {
  return makeFunctionExpression(*this, argsVect);
}

}
