#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Not NOT;

NotExpression::NotExpression(std::unique_ptr<IMathObject> &&rhs) : IUnaryExpression(std::move(rhs)) {
  function = cast<IFunction>(NOT.clone());
}

std::unique_ptr<IMathObject> NotExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<NotExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<NotExpression>(exprObj->child.get())) {
    return expr->child->clone();
  }

  return exprObj;
}

IMathObject *NotExpression::simplify() {
  simplifyExpr(child);

  if (auto *expr = cast<NotExpression>(child.get())) {
    return expr->child.release();
  }

  return this;
}

}
