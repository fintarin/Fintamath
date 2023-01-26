#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Add::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) + cast<IArithmetic>(argsVect.back().get());
}

}
