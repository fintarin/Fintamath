#include "fintamath/functions/trigonometry/Sin.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Sin::call(const ArgumentsVector &argsVect) const {
  return sin(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
