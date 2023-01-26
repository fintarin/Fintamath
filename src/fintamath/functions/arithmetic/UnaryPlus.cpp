#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr UnaryPlus::call(const ArgumentsVector &argsVect) const {
  return +cast<IArithmetic>(argsVect.front().get());
}

}
