#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(NEG, child) {
}

ArgumentPtr NegExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();

  auto simplExpr = cast<NegExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (const auto expr = cast<NegExpression>(simplExpr->child)) {
    return expr->child;
  }

  return simpl;
}

ArgumentPtr NegExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();

  auto simplExpr = cast<NegExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (auto expr = cast<INegatable>(simplExpr->child)) {
    return expr->negate();
  }

  return simpl;
}

}
