#include "fintamath/functions/arithmetic/Sub.hpp"

namespace fintamath {

MathObjectPtr Sub::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) - cast<IArithmetic>(argsVect.back().get());
}

}
