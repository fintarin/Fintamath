#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

MathObjectPtr Abs::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.front().get().to<INumber>();

  if (rhs < ZERO) {
    return -rhs;
  }

  return rhs.clone();
}

}
