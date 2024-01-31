#include "fintamath/functions/arithmetic/Sub.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Sub::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IArithmetic>(argVect.front().get());
  const auto &rhs = cast<IArithmetic>(argVect.back().get());

  return lhs - rhs;
}

}
