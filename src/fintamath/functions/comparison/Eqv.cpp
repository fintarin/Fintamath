#include "fintamath/functions/comparison/Eqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Eqv::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  const auto &rhs = argsVect.back().get();

  return Boolean(lhs == rhs).clone();
}

}
