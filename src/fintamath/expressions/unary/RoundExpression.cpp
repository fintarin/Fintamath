#include "fintamath/expressions/unary/RoundExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"

namespace fintamath {

RoundExpression::RoundExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

RoundExpression::SimplifyFunctionVector RoundExpression::getFunctionsForPostSimplify() const {
  static const RoundExpression::SimplifyFunctionVector simplifyFunctions = {
      &RoundExpression::negSimplify,
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

ArgumentPtr RoundExpression::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(makeExpr(*getOppositeFunction(func), negExpr(rhs)));
  }

  return {};
}

std::shared_ptr<IFunction> RoundExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Floor().toString(), std::make_shared<Ceil>()},
      {Ceil().toString(), std::make_shared<Floor>()},
  };
  return oppositeFunctions.at(function.toString());
}

}
