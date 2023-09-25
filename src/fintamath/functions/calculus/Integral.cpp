#include "fintamath/functions/calculus/Integral.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Integral::call(const ArgumentRefVector &argsVect) const {
  return makeExpr(*this, argsVect)->toMinimalObject();
}

}
