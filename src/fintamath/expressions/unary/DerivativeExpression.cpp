#include "fintamath/expressions/unary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Derivative DER;

DerivativeExpression::DerivativeExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(DER, inChild) {
}

ArgumentPtr DerivativeExpression::postSimplify() const {
  ArgumentPtr res;

  if (is<INumber>(child) || is<IConstant>(child)) {
    res = ZERO.clone();
  }
  else if (is<Variable>(child)) {
    res = ONE.clone();
  }
  // else if (is<IExpression>(child)) {
  // }

  return res;
}

}
