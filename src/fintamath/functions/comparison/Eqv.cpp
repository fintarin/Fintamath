#include "fintamath/functions/comparison/Eqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Eqv::call(const ArgumentsRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  const auto &rhs = argsVect.back().get();

  return std::make_unique<Boolean>(lhs == rhs);
}

}
