#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

MathObjectPtr Div::call(const ArgumentsVector &argsVect) const {
  return argsVect.front().get().to<IArithmetic>() / argsVect.back().get().to<IArithmetic>();
}

}
