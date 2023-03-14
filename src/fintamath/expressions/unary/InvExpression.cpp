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
  if (auto expr = cast<InvExpression>(child)) {
    return expr->child;
  }

  return {};
}

ArgumentPtr InvExpression::postSimplify() const {
  if (auto expr = cast<IInvertable>(child)) {
    return expr->invert();
  }

  return {};
}

}
