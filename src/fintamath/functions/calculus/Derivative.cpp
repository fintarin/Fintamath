#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Derivative::call(const ArgumentRefVector &argsVect) const {
  return makeExpr(*this, argsVect)->toMinimalObject();
}

}
