#include "fintamath/functions/calculus/Derivative.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Derivative::call(const ArgumentRefVector &argVect) const {
  return makeExpr(*this, argVect)->toMinimalObject();
}

}
