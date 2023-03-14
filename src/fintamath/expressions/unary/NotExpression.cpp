#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/expressions/interfaces/ILogicNegatable.hpp"
#include "fintamath/functions/logic/Not.hpp"

namespace fintamath {

const Not NOT;

NotExpression::NotExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(NOT, child) {
}

// unique_ptr<IMathObject> NotExpression::simplify(bool isPrecise) const {
// auto exprObj = make_unique<NotExpression>(*this);
// exprObj->simplifyValue(isPrecise);

// if (const auto *expr = cast<NotExpression>(exprObj->child)) {
//   return expr->child->clone();
// }

// return exprObj;
// }

ArgumentPtr NotExpression::preSimplify() const {
  if (const auto expr = cast<NotExpression>(child)) {
    return expr->child;
  }

  return {};
}

ArgumentPtr NotExpression::postSimplify() const {
  if (const auto expr = cast<ILogicNegatable>(child)) {
    return expr->logicNegate();
  }

  return {};
}

}
