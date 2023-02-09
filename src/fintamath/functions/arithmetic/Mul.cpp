#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

MathObjectPtr Mul::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) * cast<IArithmetic>(argsVect.back().get());
}

}
