#include "fintamath/functions/logic/Nequiv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Nequiv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Boolean>(argVect.front().get());
  const auto &rhs = cast<Boolean>(argVect.back().get());

  return Boolean(lhs != rhs).clone();
}

}
