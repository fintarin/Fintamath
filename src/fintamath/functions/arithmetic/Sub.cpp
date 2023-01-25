#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Sub::call(const ArgumentsVector &argsVect) const {
  return argsVect.front().get().to<IArithmetic>() - argsVect.back().get().to<IArithmetic>();
}

}
