#include "fintamath/functions/logic/Equiv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Equiv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Boolean>(argVect.front().get());
  const auto &rhs = cast<Boolean>(argVect.back().get());

  return Boolean(lhs == rhs).clone();
}

}
