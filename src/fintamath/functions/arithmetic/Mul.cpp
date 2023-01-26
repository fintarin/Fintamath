#include "fintamath/functions/arithmetic/Mul.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Mul::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) * cast<IArithmetic>(argsVect.back().get());
}

}
