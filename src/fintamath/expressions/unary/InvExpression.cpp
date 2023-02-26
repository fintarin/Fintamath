#include "fintamath/expressions/unary/InvExpression.hpp"

#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/numbers/INumber.hpp"
#include <memory>

namespace fintamath {

const Inv INV;

InvExpression::InvExpression(MathObjectPtr &&rhs) : IUnaryExpression(std::move(rhs)) {
  function = cast<IFunction>(INV.clone());
}

MathObjectPtr InvExpression::toMinimalObject() const {
  return simplify(false);
}

MathObjectPtr InvExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<InvExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<INumber>(exprObj->info.get())) {
    return INV(*expr);
  }

  if (auto *expr = cast<IInvertable>(exprObj->info.get())) {
    expr->invert();
    return expr->clone();
  }

  if (const auto *expr = cast<InvExpression>(exprObj->info.get())) {
    return expr->info->clone();
  }
  return exprObj;
}

}
