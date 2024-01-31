#include "fintamath/functions/comparison/Eqv.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Eqv::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = argVect.front().get();
  const auto &rhs = argVect.back().get();

  return Boolean(lhs == rhs).clone();
}

}
