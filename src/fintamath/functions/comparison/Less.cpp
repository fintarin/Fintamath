#include "fintamath/functions/comparison/Less.hpp"

#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Less::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<IComparable>(argsVect.front().get());
  const auto &rhs = cast<IComparable>(argsVect.back().get());

  // TODO! uncomment
  // if (is<Complex>(lhs) || is<Complex>(rhs)) {
  //   return {};
  // }

  return Boolean(lhs < rhs).clone();
}

}
