#include "fintamath/functions/logarithms/Lg.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Lg::call(const ArgumentsVector &argsVect) const {
  return lg(Converter::convert<Real>(argsVect.front())).simplify();
}

}
