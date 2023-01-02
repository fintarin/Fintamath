#include "fintamath/functions/arithmetic/Div.hpp"

namespace fintamath {

MathObjectPtr Div::call(const ArgumentsVector &argsVect) const {
  return argsVect.at(0).get().to<IArithmetic>() / argsVect.at(1).get().to<IArithmetic>();
}

}
