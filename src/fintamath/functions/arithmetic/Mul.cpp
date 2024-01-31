#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mul::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IArithmetic>(argVect.front().get());
  const auto &rhs = cast<IArithmetic>(argVect.back().get());

  return lhs * rhs;
}

}
