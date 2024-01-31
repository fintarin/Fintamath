#include "fintamath/functions/comparison/MoreEqv.hpp"

#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> MoreEqv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IComparable>(argVect.front().get());
  const auto &rhs = cast<IComparable>(argVect.back().get());

  if (is<Complex>(lhs) || is<Complex>(rhs)) {
    return {};
  }

  return Boolean(lhs >= rhs).clone();
}

}
