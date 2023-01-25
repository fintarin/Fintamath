#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Log::call(const ArgumentsVector &argsVect) const {
  return log(Converter::convert<Real>(argsVect.front()), Converter::convert<Real>(argsVect.back())).simplify();
}

}
