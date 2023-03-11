#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Derivative::call(const ArgumentsVector &argsVect) const {
  return makeFunctionExpression(*this, toArgumentsPtrVect(argsVect));
}

}
