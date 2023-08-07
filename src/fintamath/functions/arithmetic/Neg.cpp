#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Neg::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<IArithmetic>(argsVect.front().get());

  return -rhs;
}

}
