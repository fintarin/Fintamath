#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Log::call(const ArgumentsRefVector &argsVect) const {
  return log(convert<Real>(argsVect.front().get()), convert<Real>(argsVect.back().get())).toMinimalObject();
}

}
