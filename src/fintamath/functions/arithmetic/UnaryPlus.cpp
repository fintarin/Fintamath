#include "fintamath/functions/arithmetic/UnaryPlus.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> UnaryPlus::call(const ArgumentRefVector &argsVect) const {
  const auto &rhs = cast<IArithmetic>(argsVect.front().get());

  return +rhs;
}

}
