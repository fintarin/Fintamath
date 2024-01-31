#include "fintamath/functions/calculus/Integral.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Integral::call(const ArgumentRefVector &argVect) const {
  return makeExpr(*this, argVect)->toMinimalObject();
}

}
