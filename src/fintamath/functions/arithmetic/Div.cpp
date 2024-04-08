#include "fintamath/functions/arithmetic/Div.hpp"

#include <memory>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Div)

std::unique_ptr<IMathObject> Div::call(const ArgumentRefVector &argVect) const {
  const auto &lhs = cast<IArithmetic>(argVect.front().get());
  const auto &rhs = cast<IArithmetic>(argVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Undefined{}.clone();
  }

  if (rhs == Integer(0)) {
    return ComplexInf{}.clone();
  }

  return lhs / rhs;
}

}
