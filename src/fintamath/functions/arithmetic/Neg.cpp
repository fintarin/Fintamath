#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

MathObjectPtr Neg::call(const ArgumentsVector &argsVect) const {
  return -cast<IArithmetic>(argsVect.front().get());
}

}
