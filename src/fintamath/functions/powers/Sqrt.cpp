#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sqrt::call(const ArgumentsRefVector &argsVect) const {
  return sqrt(cast<INumber>(argsVect.front().get()));
}

}
