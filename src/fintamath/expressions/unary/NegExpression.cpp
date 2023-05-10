#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/interfaces/INegatableExpression.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"

namespace fintamath {

NegExpression::NegExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(Neg(), inChild) {
}

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::simplifyNestedNeg, //
  };
  return simplifyFunctions;
}

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForPreSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::callNegFunction, //
  };
  return simplifyFunctions;
}

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForPostSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::simplifyNegatable, //
  };
  return simplifyFunctions;
}

ArgumentPtr NegExpression::callNegFunction(const ArgumentPtr &rhs) {
  if (ArgumentPtr res = callFunction(Neg(), {rhs})) {
    return res;
  }

  return {};
}

ArgumentPtr NegExpression::simplifyNegatable(const ArgumentPtr &rhs) {
  if (auto expr = cast<INegatableExpression>(rhs)) {
    return expr->negate();
  }

  return {};
}

ArgumentPtr NegExpression::simplifyNestedNeg(const ArgumentPtr &rhs) {
  if (const auto expr = cast<NegExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
