#include "fintamath/functions/arithmetic/Sub.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Sub::call(const ArgumentsVector &argsVect) const {
  return argsVect.at(0).get().to<IArithmetic>() - argsVect.at(1).get().to<IArithmetic>();
}

}
