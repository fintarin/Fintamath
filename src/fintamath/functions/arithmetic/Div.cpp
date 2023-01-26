#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Div::call(const ArgumentsVector &argsVect) const {
  return cast<IArithmetic>(argsVect.front().get()) / cast<IArithmetic>(argsVect.back().get());
}

}
