#include "fintamath/expressions/InvExpression.hpp"
#include "fintamath/expressions/IInvertable.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include <memory>

namespace fintamath {

const Inv INV;

InvExpression::InvExpression(const IMathObject &rhs) : IUnaryExpression(rhs) {
}

InvExpression::InvExpression(const MathObjectPtr &rhs) : IUnaryExpression(rhs) {
}

MathObjectPtr InvExpression::simplify() const {
  return simplify(false);
}

MathObjectPtr InvExpression::simplify(bool isPrecise) const {
  auto exprObj = std::make_unique<InvExpression>(*this);
  exprObj->simplifyValue(isPrecise);

  if (const auto *expr = cast<IArithmetic>(exprObj->info.get())) {
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

const IFunction *InvExpression::getFunction() const {
  return &INV;
}

}
