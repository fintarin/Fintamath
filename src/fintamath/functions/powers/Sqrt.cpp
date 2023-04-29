#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentsRefVector &argsVect) const {
  return sqrt(convert<Real>(argsVect.front())).toMinimalObject();
}

}
