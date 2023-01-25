#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Mul::call(const ArgumentsVector &argsVect) const {
  return argsVect.front().get().to<IArithmetic>() * argsVect.back().get().to<IArithmetic>();
}

}
