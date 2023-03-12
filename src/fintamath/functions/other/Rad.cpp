#include "fintamath/functions/other/Rad.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/literals/constants/Pi.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/NumberFunctions.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Rad::call(const ArgumentsRefVector &argsVect) const {
  const auto &rhs = cast<INumber>(argsVect.front().get());
  static const Integer ANGLE = 180;
  return rhs * (PI_NUM / ANGLE);
}

}
