#include "fintamath/expressions/binary/IntegralExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/calculus/Integral.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

IntegralExpression::IntegralExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Integral(), inLhsChild, inRhsChild) {
}

IntegralExpression::SimplifyFunctionsVector IntegralExpression::getFunctionsForPostSimplify() const {
  static const IntegralExpression::SimplifyFunctionsVector simplifyFunctions = {
      &IntegralExpression::integralSimplify, //
  };
  return simplifyFunctions;
}

ArgumentPtr IntegralExpression::integralSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  // TODO: remove this and implement derivative with rhs !is Variable
  if (!is<Variable>(rhs)) {
    throw InvalidInputFunctionException(Integral().toString(), {lhs->toString(), rhs->toString()});
  }

  ArgumentPtr res;

  if (is<INumber>(lhs) || is<IConstant>(lhs)) {
    res = makeFunctionExpression(Mul(), lhs, rhs);
  }
  else if (is<Variable>(lhs) && is<Variable>(rhs) && *lhs == *rhs) {
    res = makeFunctionExpression(Div(), makeRawFunctionExpression(Pow(), lhs, TWO.clone()), TWO.clone());
  }

  // TODO: res + integral constant

  return res;
}

}
