#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

const Not NOT;

const NotExpression::SimplifyFunctionsVector NotExpression::simplifyFunctions = {
    &NotExpression::simplifyNot, //
};

NotExpression::NotExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(NOT, inChild) {
}

ArgumentPtr NotExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();
  auto simplExpr = cast<NotExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (ArgumentPtr res = callFunction(*simplExpr->func, {simplExpr->child})) {
    return res;
  }

  return simpl;
}

ArgumentPtr NotExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();
  auto simplExpr = cast<NotExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (const auto expr = cast<ILogicNegatableExpression>(simplExpr->child)) {
    return expr->logicNegate();
  }

  return simpl;
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForSimplify() const {
  return simplifyFunctions;
}

ArgumentPtr NotExpression::simplifyNot(const ArgumentPtr &rhs) {
  if (const auto expr = cast<NotExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
