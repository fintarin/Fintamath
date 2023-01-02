#include "fintamath/functions/trigonometry/Cos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Cos::call(const ArgumentsVector &argsVect) const {
  return cos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
