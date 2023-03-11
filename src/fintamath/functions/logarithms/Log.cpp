#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Log::call(const ArgumentsVector &argsVect) const {
  return log(convert<Real>(argsVect.front()), convert<Real>(argsVect.back())).toMinimalObject();
}

}
