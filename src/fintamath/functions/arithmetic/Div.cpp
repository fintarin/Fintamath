#include "fintamath/functions/arithmetic/Div.hpp"

#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

std::unique_ptr<IMathObject> Div::call(const ArgumentRefVector &argsVect) const {
  const auto &lhs = cast<IArithmetic>(argsVect.front().get());
  const auto &rhs = cast<IArithmetic>(argsVect.back().get());

  if (lhs == Integer(0) && rhs == Integer(0)) {
    return Undefined().clone();
  }

  if (rhs == Integer(0)) {
    return ComplexInf().clone();
  }

  return lhs / rhs;
}

}
