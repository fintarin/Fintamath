#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {

MathObjectPtr UnaryPlus::call(const ArgumentsVector &argsVect) const {
  return +cast<IArithmetic>(argsVect.front().get());
}

}
