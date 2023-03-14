#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

unique_ptr<IMathObject> Log::call(const ArgumentsRefVector &argsVect) const {
  return log(convert<Real>(argsVect.front()), convert<Real>(argsVect.back())).toMinimalObject();
}

}
