#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Acot::call(const ArgumentsVector &argsVect) const {
  return acot(Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
