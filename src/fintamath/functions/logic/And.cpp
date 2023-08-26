#include "fintamath/functions/logic/And.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> And::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<Boolean>(argsVect.front().get());
  const auto &rhs = cast<Boolean>(argsVect.back().get());

  return Boolean(lhs && rhs).clone();
}

}
