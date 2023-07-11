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

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForPreSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::callNegFunction,   //
      &NegExpression::simplifyNestedNeg, //
  };
  return simplifyFunctions;
}

NegExpression::SimplifyFunctionsVector NegExpression::getFunctionsForPostSimplify() const {
  static const NegExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NegExpression::simplifyNegatable, //
      &NegExpression::simplifyNestedNeg, //
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

  ArgumentPtr res;
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  if (is<Add>(rhsExpr->getFunction())) {
    for (auto &child : rhsChildren) {
      child = makeExpr(Neg(), child);
    }

    res = makeExpr(Add(), rhsChildren);
  }
  else if (is<Mul>(rhsExpr->getFunction())) {
    rhsChildren.emplace_back(std::make_shared<Integer>(-1));
    res = makeExpr(Mul(), rhsChildren);
  }
  else if (is<Log>(rhsExpr->getFunction())) {
    ArgumentPtr logLhs = rhsChildren.front();
    ArgumentPtr logRhs = makeExpr(Div(), std::make_shared<Integer>(1), rhsChildren.back());
    res = makeExpr(Log(), logLhs, logRhs);
  }

  return res;
}

ArgumentPtr NegExpression::simplifyNestedNeg(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (const auto expr = cast<NegExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

}
