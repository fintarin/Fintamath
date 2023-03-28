#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(NEG, child) {
}

// unique_ptr<IMathObject> NegExpression::simplify(bool isPrecise) const {
// auto exprObj = make_unique<NegExpression>(*this);
// exprObj->simplifyValue(isPrecise);

// if (const auto *expr = cast<INumber>(exprObj->child)) {
//   return -(*expr);
// }

// if (auto *expr = cast<INegatable>(exprObj->child)) {
//   expr->negate();
//   return expr->clone();
// }

// if (const auto *expr = cast<NegExpression>(exprObj->child)) {
//   return expr->child->clone();
// }

// return exprObj;
// }

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
