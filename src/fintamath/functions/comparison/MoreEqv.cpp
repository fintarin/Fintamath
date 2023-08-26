#include "fintamath/functions/comparison/MoreEqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> MoreEqv::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<IComparable>(argsVect.front().get());
  const auto &rhs = cast<IComparable>(argsVect.back().get());

  // TODO! uncomment
  // if (is<Complex>(lhs) || is<Complex>(rhs)) {
  //   return {};
  // }

  return Boolean(lhs >= rhs).clone();
}

}
