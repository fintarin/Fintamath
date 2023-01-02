#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

MathObjectPtr Mul::call(const ArgumentsVector &argsVect) const {
  return argsVect.at(0).get().to<IArithmetic>() * argsVect.at(1).get().to<IArithmetic>();
}

}
