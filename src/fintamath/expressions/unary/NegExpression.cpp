#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/INegatableExpression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

NegExpression::NegExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(Neg(), inChild) {
}

ArgumentPtr NegExpression::preSimplify() const {
  auto simpl = IUnaryExpression::preSimplify();
  auto simplExpr = cast<NegExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (ArgumentPtr res = callFunction(*simplExpr->func, {simplExpr->child})) {
    return res;
  }

  return simpl;
}

ArgumentPtr NegExpression::postSimplify() const {
  auto simpl = IUnaryExpression::postSimplify();
  auto simplExpr = cast<NegExpression>(simpl);

  if (!simplExpr) {
    return simpl;
  }

  if (auto expr = cast<INegatableExpression>(simplExpr->child)) {
    return expr->negate();
  }

  return simpl;
}

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::simplifyNeg, //
  };
  return simplifyFunctions;
}

ArgumentPtr NegExpression::simplifyNeg(const ArgumentPtr &rhs) {
  if (const auto expr = cast<NegExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
