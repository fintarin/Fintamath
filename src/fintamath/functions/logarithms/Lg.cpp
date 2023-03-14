#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Lg::call(const ArgumentsRefVector &argsVect) const {
  return lg(convert<Real>(argsVect.front())).toMinimalObject();
}

}
