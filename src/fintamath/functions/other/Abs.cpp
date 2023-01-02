#include "fintamath/functions/other/Abs.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

MathObjectPtr Abs::call(const ArgumentsVector &argsVect) const {
  const auto &rhs = argsVect.at(0).get().to<INumber>();

  if (rhs < Integer(0)) {
    return -rhs;
  }

  return rhs.clone();
}

}
