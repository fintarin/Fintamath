#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cos::call(const ArgumentsVector &argsVect) const {
  return cos(Converter::convert<Real>(argsVect.front())).simplify();
}

}
