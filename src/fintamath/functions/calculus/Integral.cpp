#include "fintamath/functions/calculus/Integral.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Integral::call(const ArgumentsRefVector &argsVect) const {
  return makeFunctionExpression(*this, argsVect);
}

}
