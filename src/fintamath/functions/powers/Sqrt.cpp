#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Sqrt::call(const ArgumentsVector &argsVect) const {
  return sqrt(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
