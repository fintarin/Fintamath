#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Not NOT;

NotExpression::NotExpression(MathObjectPtr &&rhs) : IUnaryExpression(std::move(rhs)) {
}

MathObjectPtr NotExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr NotExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<NotExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<NotExpression>(exprObj->info.get())) {
    return expr->info->clone();
  }

  return exprObj;
}

const IFunction *NotExpression::getFunction() const {
  return &NOT;
}

}
