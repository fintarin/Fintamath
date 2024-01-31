#include "fintamath/functions/logic/Impl.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Impl::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<Boolean>(argVect.front().get());
  const auto &rhs = cast<Boolean>(argVect.back().get());

  return Boolean(!lhs || rhs).clone();
}

}
