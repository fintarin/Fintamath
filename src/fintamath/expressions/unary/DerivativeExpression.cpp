#include "fintamath/expressions/unary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Derivative DER;

DerivativeExpression::DerivativeExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(DER, child) {
}

ArgumentPtr DerivativeExpression::postSimplify() const {
  if (is<IExpression>(child)) {
    // TODO: implement derivative of expression
    return {};
  }

  if (is<INumber>(child) || is<IConstant>(child)) {
    return ZERO.clone();
  }
  if (is<Variable>(child)) {
    return ONE.clone();
  }

  return {};
}

}
