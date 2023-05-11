#include "fintamath/functions/other/Degrees.hpp"

#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/RealFunctions.hpp"

namespace fintamath {

const Integer ANGLE = 180;

std::unique_ptr<IMathObject> Degrees::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());
  return rhs * (ANGLE / getPi());
}

}
