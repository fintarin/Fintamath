#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> UnaryPlus::call(const ArgumentRefVector &argVect) const {
  const auto &rhs = cast<IArithmetic>(argVect.front().get());

  return +rhs;
}

}
