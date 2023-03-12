#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pow::call(const ArgumentsRefVector &argsVect) const {
  return pow(cast<INumber>(argsVect.front().get()), cast<INumber>(argsVect.back().get()));
}

}
