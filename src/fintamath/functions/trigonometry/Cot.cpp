#include "fintamath/functions/trigonometry/Cot.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cot::call(const ArgumentsVector &argsVect) const {
  return cot(Converter::convert<Real>(argsVect.front())).simplify();
}

}
