#include "fintamath/expressions/unary/NegExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/logarithms/Log.hpp"

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

ArgumentPtr NegExpression::callNegFunction(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (ArgumentPtr res = callFunction(Neg(), {rhs})) {
    return res;
  }

  return {};
}

ArgumentPtr NegExpression::simplifyNegatable(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!rhsExpr) {
    return {};
  }

  if (is<Add>(rhsExpr->getFunction())) {
    ArgumentsPtrVector children = rhsExpr->getChildren();
    for (auto &child : children) {
      child = makeExpr(Neg(), child);
    }

    return makeExpr(Add(), children)->toMinimalObject();
  }

  if (is<Mul>(rhsExpr->getFunction())) {
    ArgumentsPtrVector children = rhsExpr->getChildren();
    children.emplace_back(std::make_shared<Integer>(-1));
    return makeExpr(Mul(), children)->toMinimalObject();
  }

  if (is<Log>(rhsExpr->getFunction())) {
    ArgumentsPtrVector children = rhsExpr->getChildren();
    return makeExpr(Log(), children.front(), makeExpr(Div(), std::make_shared<Integer>(1), children.back()))
        ->toMinimalObject();
  }

  return {};
}

ArgumentPtr NegExpression::simplifyNestedNeg(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (const auto expr = cast<NegExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
