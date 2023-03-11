#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Exp::call(const ArgumentsVector &argsVect) const {
  return exp(convert<Real>(argsVect.front())).toMinimalObject();
}

}
