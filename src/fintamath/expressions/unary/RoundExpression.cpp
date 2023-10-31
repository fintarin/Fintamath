#include "fintamath/expressions/unary/RoundExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"

namespace fintamath {

RoundExpression::RoundExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

RoundExpression::SimplifyFunctionVector RoundExpression::getFunctionsForPostSimplify() const {
  static const RoundExpression::SimplifyFunctionVector simplifyFunctions = {
      &RoundExpression::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr RoundExpression::intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  return callFunction(func, {approx});
}

}
