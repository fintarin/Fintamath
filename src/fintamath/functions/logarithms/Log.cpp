#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Log::call(const ArgumentsVector &argsVect) const {
  return log(helpers::Converter::convert<Real>(argsVect.at(0)), helpers::Converter::convert<Real>(argsVect.at(1)))
      .simplify();
}

}
