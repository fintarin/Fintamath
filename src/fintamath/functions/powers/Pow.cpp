#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

MathObjectPtr Pow::call(const ArgumentsVector &argsVect) const {
  return pow(argsVect.front().get().to<INumber>(), argsVect.back().get().to<INumber>());
}

}
