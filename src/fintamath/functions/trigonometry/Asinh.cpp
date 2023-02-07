#include "fintamath/functions/trigonometry/Asinh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Asinh::call(const ArgumentsVector &argsVect) const {
  return asinh(convert<Real>(argsVect.front())).simplify();
}

}
