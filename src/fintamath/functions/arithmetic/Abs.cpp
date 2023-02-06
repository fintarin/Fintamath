#include "fintamath/functions/arithmetic/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

MathObjectPtr Abs::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  if (rhs < ZERO) {
    return -rhs;
  }

  return rhs.clone();
}

}
