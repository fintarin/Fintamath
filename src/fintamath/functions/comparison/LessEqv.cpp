#include "fintamath/functions/comparison/LessEqv.hpp"

#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> LessEqv::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<IComparable>(argsVect.front().get());
  const auto &rhs = cast<IComparable>(argsVect.back().get());

  if (is<Complex>(lhs) || is<Complex>(rhs)) {
    return {};
  }

  return Boolean(lhs <= rhs).clone();
}

}
