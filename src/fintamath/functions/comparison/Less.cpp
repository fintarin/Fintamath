#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Less::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IComparable>(argVect.front().get());
  const auto &rhs = cast<IComparable>(argVect.back().get());

  if (is<Complex>(lhs) || is<Complex>(rhs)) {
    return {};
  }

  return Boolean(lhs < rhs).clone();
}

}
