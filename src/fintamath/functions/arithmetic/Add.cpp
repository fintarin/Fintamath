#include "fintamath/functions/arithmetic/Add.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Add::call(const ArgumentsVector &argsVect) const {
  return argsVect.at(0).get().to<IArithmetic>() + argsVect.at(1).get().to<IArithmetic>();
}

}
