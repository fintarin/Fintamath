#include "fintamath/expressions/unary/InvExpression.hpp"

#include "fintamath/expressions/interfaces/IInvertable.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"

namespace fintamath {

const Inv INV;

InvExpression::InvExpression(const ArgumentPtr &child) : IUnaryExpressionCRTP(INV, child) {
}

ArgumentPtr InvExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();

  auto simplExpr = cast<InvExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }
  if (const auto expr = cast<InvExpression>(simplExpr->child)) {
    return expr->child;
  }

  return simpl;
}

ArgumentPtr InvExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();

  auto simplExpr = cast<InvExpression>(simpl);
  if (!simplExpr) {
    return simpl;
  }

  if (auto expr = cast<IInvertable>(simplExpr->child)) {
    return expr->invert();
  }

  return simpl;
}

string InvExpression::toString() const {
  string childToStr = getChildren()[0]->toString();
  if (const auto &sumChildExpr = cast<IExpression>(getChildren()[0]);
      sumChildExpr && is<Add>(sumChildExpr->getFunction())) {
    childToStr = ("(" + childToStr + ")");
  }
  return "1/" + childToStr;
}


}
