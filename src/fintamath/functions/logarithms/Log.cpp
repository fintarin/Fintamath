#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Log::call(const ArgumentsVector &argsVect) const {
  return log(convert<Real>(argsVect.front()), convert<Real>(argsVect.back())).toMinimalObject();
}

}
