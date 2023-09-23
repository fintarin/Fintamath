#include "fintamath/functions/arithmetic/Mul.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Mul::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = cast<IArithmetic>(argsVect.front().get());
  const auto &rhs = cast<IArithmetic>(argsVect.back().get());

  return lhs * rhs;
}

}
