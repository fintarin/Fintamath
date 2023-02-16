#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

MathObjectPtr Sqrt::call(const ArgumentsVector &argsVect) const {
  return sqrt(convert<Real>(argsVect.front())).toMinimalObject();
}

}
