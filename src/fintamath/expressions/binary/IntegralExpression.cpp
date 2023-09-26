#include "fintamath/expressions/binary/IntegralExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/calculus/Integral.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

IntegralExpression::IntegralExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Integral(), std::move(inLhsChild), std::move(inRhsChild)) {
}

IntegralExpression::SimplifyFunctionVector IntegralExpression::getFunctionsForPostSimplify() const {
  static const IntegralExpression::SimplifyFunctionVector simplifyFunctions = {
      &IntegralExpression::integralSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr IntegralExpression::integralSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  // TODO: remove this and implement derivative with rhs !is Variable
  if (!is<Variable>(rhs)) {
    throw InvalidInputFunctionException(Integral().toString(), {lhs->toString(), rhs->toString()});
  }

  ArgumentPtr res;

  if (is<INumber>(lhs) || is<IConstant>(lhs)) {
    res = mulExpr(lhs, rhs);
  }
  else if (is<Variable>(lhs) && is<Variable>(rhs) && *lhs == *rhs) {
    res = divExpr(powExpr(lhs, Integer(2).clone()), Integer(2).clone());
  }

  // TODO: res + integral constant

  return res;
}

}
