#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Exp::call(const ArgumentsRefVector &argsVect) const {
  return exp(convert<Real>(argsVect.front())).toMinimalObject();
}

}
