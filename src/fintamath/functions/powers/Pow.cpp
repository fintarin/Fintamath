#include "fintamath/functions/powers/Pow.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Pow::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<INumber>(argsVect.front().get());
  const auto &rhs = cast<INumber>(argsVect.back().get());

  if (rhs < Integer(0)) {
    return pow(*(Integer(1) / lhs), *(-rhs));
  }

  return pow(lhs, rhs);
}

}
