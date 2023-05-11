#include "fintamath/functions/other/Rad.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

const Integer ANGLE = 180;

std::unique_ptr<IMathObject> Rad::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());
  return rhs * (getPi() / ANGLE);
}

}
