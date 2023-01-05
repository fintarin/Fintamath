#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr UnaryPlus::call(const ArgumentsVector &argsVect) const {
  return +argsVect.at(0).get().to<IArithmetic>();
}

}
