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
  if (const auto expr = cast<NegExpression>(child)) {
    return expr->child;
  }

  return {};
}

ArgumentPtr NegExpression::postSimplify() const {
  if (auto expr = cast<INegatable>(child)) {
    return expr->negate();
  }

  return {};
}

}
