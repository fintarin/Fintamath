#include "fintamath/functions/logic/Impl.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Impl::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = cast<Boolean>(argsVect.front().get());
  const auto &rhs = cast<Boolean>(argsVect.back().get());

  return Boolean(!lhs || rhs).clone();
}

}
