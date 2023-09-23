#include "fintamath/functions/comparison/Neqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Neqv::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = argsVect.front().get();
  const auto &rhs = argsVect.back().get();

  return Boolean(lhs != rhs).clone();
}

}
