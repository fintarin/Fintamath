#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/INegatable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Neg NEG;

NegExpression::NegExpression(std::shared_ptr<IMathObject> child) : IUnaryExpression(NEG, std::move(child)) {
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

std::shared_ptr<IMathObject> NegExpression::simplify() {
  simplifyExpr(child);

  if (function->doArgsMatch({*child})) {
    return (*function)(*child);
  }

  if (const auto expr = cast<INegatable>(child)) {
    expr->negate();
    return child;
  }

  if (const auto expr = cast<NegExpression>(child)) {
    return expr->child;
  }

  return shared_from_this();
}

}
