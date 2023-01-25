#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Sqrt::call(const ArgumentsVector &argsVect) const {
  return sqrt(Converter::convert<Real>(argsVect.front())).simplify();
}

}
