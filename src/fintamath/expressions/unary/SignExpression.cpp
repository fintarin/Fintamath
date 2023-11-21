#include "fintamath/expressions/unary/SignExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sign.hpp"

namespace fintamath {

SignExpression::SignExpression(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Sign(), std::move(inChild)) {
}

SignExpression::SimplifyFunctionVector SignExpression::getFunctionsForPostSimplify() const {
  static const SignExpression::SimplifyFunctionVector simplifyFunctions = {
      &SignExpression::negSimplify,
      &SignExpression::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr SignExpression::intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  if (const auto approxNum = cast<INumber>(approx); approxNum && !approxNum->isComplex()) {
    return callFunction(func, {approx});
  }

  return {};
}

ArgumentPtr SignExpression::negSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(signExpr(negExpr(rhs)));
  }

  return {};
}

}
