#include "fintamath/expressions/NegExpression.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/expressions/MulExpression.hpp"
#include "fintamath/expressions/PolynomExpression.hpp"
#include "fintamath/expressions/SumExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

MathObjectPtr NegExpression::simplify() const {
  return simplify(false);
}

MathObjectPtr NegExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<NegExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<IArithmetic>(exprObj->info.get())) {
    return -*expr;
  }

  if (auto *expr = cast<SumExpression>(exprObj->info.get())) {
    expr->negate();
    return expr->clone();
  }

  if (auto *expr = cast<MulExpression>(exprObj->info.get())) {
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