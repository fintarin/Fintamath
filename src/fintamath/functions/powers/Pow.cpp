#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

MathObjectPtr Pow::call(const ArgumentsVector &argsVect) const {
  return pow(argsVect.at(0).get().to<INumber>(), argsVect.at(1).get().to<INumber>());
}

}
