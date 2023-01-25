#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Add::call(const ArgumentsVector &argsVect) const {
  return argsVect.front().get().to<IArithmetic>() + argsVect.back().get().to<IArithmetic>();
}

}
