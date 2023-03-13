#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/interfaces/INegatable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(const std::shared_ptr<IMathObject> &child) : IUnaryExpressionCRTP(NEG, child) {
}

std::unique_ptr<IMathObject> NegExpression::simplify(bool isPrecise) const {
  // auto exprObj = std::make_unique<NegExpression>(*this);
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

  return std::make_unique<NegExpression>(*this);
}

std::shared_ptr<IMathObject> NegExpression::preSimplify() const {
  if (const auto expr = cast<NegExpression>(child)) {
    return expr->child;
  }

  return {};
}

std::shared_ptr<IMathObject> NegExpression::postSimplify() const {
  if (auto expr = cast<INegatable>(child)) {
    expr->negate();
    auto res = cast<IMathObject>(expr);
    simplifyChild(res);
    return res;
  }

  return {};
}

}
