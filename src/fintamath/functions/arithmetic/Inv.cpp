#include "fintamath/functions/arithmetic/Inv.hpp"

#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

MathObjectPtr Inv::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());

  return ONE / rhs;
}

}