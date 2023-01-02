#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

MathObjectPtr Neg::call(const ArgumentsVector &argsVect) const {
  return -argsVect.at(0).get().to<IArithmetic>();
}

}
