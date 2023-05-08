#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Abs::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());
  return abs(rhs);
}

}
