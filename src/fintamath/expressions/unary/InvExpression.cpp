#include "fintamath/expressions/unary/InvExpression.hpp"

#include "fintamath/expressions/interfaces/IInvertable.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"

namespace fintamath {

const Inv INV;

InvExpression::InvExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(INV, child) {
}

// unique_ptr<IMathObject> InvExpression::simplify(bool isPrecise) const {
// auto exprObj = make_unique<InvExpression>(*this);
// exprObj->simplifyValue(isPrecise);

// if (const auto *expr = cast<INumber>(exprObj->child)) {
//   return INV(*expr);
// }

// if (auto *expr = cast<IInvertable>(exprObj->child)) {
//   expr->invert();
//   return expr->clone();
// }

// if (const auto *expr = cast<InvExpression>(exprObj->child)) {
//   return expr->child->clone();
// }
// return exprObj;
// }

ArgumentPtr InvExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();

  auto simplExpr = cast<InvExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }
  if (const auto expr = cast<InvExpression>(simplExpr->child)) {
    return expr->child;
  }

  return simpl;
}

ArgumentPtr InvExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();

  auto simplExpr = cast<InvExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (auto expr = cast<IInvertable>(simplExpr->child)) {
    return expr->invert();
  }

  return simpl;
}

}
