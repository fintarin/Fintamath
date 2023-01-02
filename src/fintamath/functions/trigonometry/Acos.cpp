#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Acos::call(const ArgumentsVector &argsVect) const {
  return acos(helpers::Converter::convert<Real>(argsVect.at(0))).simplify();
}

}
