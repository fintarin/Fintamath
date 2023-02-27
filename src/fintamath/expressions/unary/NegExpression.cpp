#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

NegExpression::NegExpression(MathObjectPtr &&rhs) : IUnaryExpression(std::move(rhs)) {
  function = cast<IFunction>(Neg().clone());
}

MathObjectPtr NegExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<NegExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<INumber>(exprObj->child.get())) {
    return -(*expr);
  }

  if (auto *expr = cast<INegatable>(exprObj->child.get())) {
    expr->negate();
    return expr->clone();
  }

  if (const auto *expr = cast<NegExpression>(exprObj->child.get())) {
    return expr->child->clone();
  }

  return exprObj;
}

IMathObject *NegExpression::simplify() {
  simplifyExpr(child);

  if (function->doArgsMatch({*child})) {
    return (*function)(*child).release();
  }

  if (auto *expr = cast<INegatable>(child.get())) {
    expr->negate();
    return expr;
  }

  if (auto *expr = cast<NegExpression>(child.get())) {
    return expr->child.release();
  }

  return this;
}

}
