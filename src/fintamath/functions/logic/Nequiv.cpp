#include "fintamath/functions/logic/Nequiv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Nequiv::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = cast<Boolean>(argsVect.front().get());
  const auto &rhs = cast<Boolean>(argsVect.back().get());

  return std::make_unique<Boolean>(lhs != rhs);
}

}
