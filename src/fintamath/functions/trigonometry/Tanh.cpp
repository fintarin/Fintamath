#include "fintamath/functions/trigonometry/Tanh.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Tanh::call(const ArgumentsVector &argsVect) const {
  return tanh(convert<Real>(argsVect.front())).simplify();
}

}
