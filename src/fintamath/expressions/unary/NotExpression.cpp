#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Not NOT;

NotExpression::NotExpression(std::shared_ptr<IMathObject> child) : IUnaryExpression(NOT, std::move(child)) {
}

std::unique_ptr<IMathObject> NotExpression::simplify(bool isPrecise) const {
  // auto exprObj = std::make_unique<NotExpression>(*this);
  // exprObj->simplifyValue(isPrecise);

  // if (const auto *expr = cast<NotExpression>(exprObj->child)) {
  //   return expr->child->clone();
  // }

  // return exprObj;

  return std::make_unique<NotExpression>(*this);
}

std::shared_ptr<IMathObject> NotExpression::simplifyChildren() {
  if (const auto expr = cast<NotExpression>(child)) {
    return expr->child;
  }

  return nullptr;
}

}
