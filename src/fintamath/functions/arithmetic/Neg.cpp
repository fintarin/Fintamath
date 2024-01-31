#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Neg::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<IArithmetic>(argVect.front().get());

  return -rhs;
}

}
