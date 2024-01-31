#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Or::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Boolean>(argVect.front().get());
  const auto &rhs = cast<Boolean>(argVect.back().get());

  return Boolean(lhs || rhs).clone();
}

}
