#include "fintamath/functions/arithmetic/Inv.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

unique_ptr<IMathObject> Inv::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return ONE / rhs;
}

}