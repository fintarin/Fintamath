#include "fintamath/expressions/NegExpression.hpp"

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const IMathObject &rhs) : IUnaryExpression(rhs) {
}

NegExpression::NegExpression(MathObjectPtr &&rhs) : IUnaryExpression(std::move(rhs)) {
}

MathObjectPtr NegExpression::simplify() const {
  return simplify(false);
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<NegExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<INumber>(exprObj->info.get())) {
    return -*expr;
  }

  if (auto *expr = cast<INegatable>(exprObj->info.get())) {
    expr->negate();
    return expr->clone();
  }

  if (const auto *expr = cast<NegExpression>(exprObj->info.get())) {
    return expr->info->clone();
  }
  return exprObj;
}

const IFunction *NegExpression::getFunction() const {
  return &NEG;
}

}
