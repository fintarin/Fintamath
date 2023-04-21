#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/expressions/ILogicNegatableExpression.hpp"
#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

const Not NOT;

NotExpression::NotExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(NOT, child) {
}

ArgumentPtr NotExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();

  auto simplExpr = cast<NotExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (const auto expr = cast<NotExpression>(simplExpr->child)) {
    return expr->child;
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

}
