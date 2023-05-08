#include "fintamath/expressions/binary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

DerivativeExpression::DerivativeExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Derivative(), inLhsChild, inRhsChild) {
}

ArgumentPtr DerivativeExpression::postSimplify() const {
  ArgumentPtr res;

  if (is<INumber>(lhsChild) || is<IConstant>(lhsChild)) {
    res = ZERO.clone();
  }
  else if (is<Variable>(lhsChild) && *lhsChild == *rhsChild) {
    res = ONE.clone();
  }

  return res;
}

}
