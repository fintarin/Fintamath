#include "fintamath/expressions/unary/FloorCeilExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/ntheory/Ceil.hpp"
#include "fintamath/functions/ntheory/Floor.hpp"

namespace fintamath {

FloorCeilExpression::FloorCeilExpression(const IFunction &inFunc, ArgumentPtr inChild)
    : IUnaryExpressionCRTP(inFunc, std::move(inChild)) {
}

FloorCeilExpression::SimplifyFunctionVector FloorCeilExpression::getFunctionsForPostSimplify() const {
  static const FloorCeilExpression::SimplifyFunctionVector simplifyFunctions = {
      &FloorCeilExpression::negSimplify,
      &FloorCeilExpression::intApproximateSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr FloorCeilExpression::intApproximateSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (containsVariable(rhs)) {
    return {};
  }

  ArgumentPtr approx = rhs->clone();
  approximateSimplifyChild(approx);

  if (auto res = cast<INumber>(callFunction(func, {approx}))) {
    return res;
  }

  return {};
}

ArgumentPtr FloorCeilExpression::negSimplify(const IFunction &func, const ArgumentPtr &rhs) {
  if (isNegated(rhs)) {
    return negExpr(makeExpr(*getOppositeFunction(func), negExpr(rhs)));
  }

  return {};
}

std::shared_ptr<IFunction> FloorCeilExpression::getOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Floor().toString(), std::make_shared<Ceil>()},
      {Ceil().toString(), std::make_shared<Floor>()},
  };
  return oppositeFunctions.at(function.toString());
}

}
