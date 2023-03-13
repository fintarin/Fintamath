#include "fintamath/expressions/unary/InvExpression.hpp"

#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Inv INV;

InvExpression::InvExpression(const std::shared_ptr<IMathObject> &child) : IUnaryExpressionCRTP(INV, child) {
}

std::unique_ptr<IMathObject> InvExpression::simplify(bool isPrecise) const {
  // auto exprObj = std::make_unique<InvExpression>(*this);
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

  return std::make_unique<InvExpression>(*this);
}

std::shared_ptr<IMathObject> InvExpression::preSimplify() const {
  if (auto expr = cast<InvExpression>(child)) {
    return expr->child;
  }

  return {};
}

std::shared_ptr<IMathObject> InvExpression::postSimplify() const {
  if (auto expr = cast<IInvertable>(child)) {
    expr->invert();
    auto res = cast<IMathObject>(expr);
    simplifyChild(res);
    return res;
  }

  return {};
}

}
