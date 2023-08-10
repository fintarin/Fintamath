#include "fintamath/expressions/binary/LogExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"
#include "fintamath/functions/logarithms/Lg.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

LogExpression::LogExpression(const ArgumentPtr &inLhsChild, const ArgumentPtr &inRhsChild)
    : IBinaryExpressionCRTP(Log(), inLhsChild, inRhsChild) {
}

std::string LogExpression::toString() const {
  if (*lhsChild == E()) {
    return functionToString(Ln(), {rhsChild});
  }

  return IBinaryExpression::toString();
}

std::shared_ptr<IFunction> LogExpression::getOutputFunction() const {
  if (*lhsChild == E()) {
    return std::make_shared<Ln>();
  }

  return IBinaryExpression::getFunction();
}

ArgumentPtr LogExpression::preciseSimplify() const {
  if (*lhsChild == E()) {
    auto preciseExpr = cast<LogExpression>(clone());
    preciseSimplifyChild(preciseExpr->rhsChild);
    return preciseExpr;
  }

  return IBinaryExpression::preciseSimplify();
}

LogExpression::SimplifyFunctionsVector LogExpression::getFunctionsForPreSimplify() const {
  static const LogExpression::SimplifyFunctionsVector simplifyFunctions = {
      &LogExpression::callFunctionSimplify,
      &LogExpression::equalSimplify,
      &LogExpression::powSimplify,
  };
  return simplifyFunctions;
}

LogExpression::SimplifyFunctionsVector LogExpression::getFunctionsForPostSimplify() const {
  static const LogExpression::SimplifyFunctionsVector simplifyFunctions = {
      &LogExpression::constSimplify,
      &LogExpression::powSimplify,
      &LogExpression::equalSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr LogExpression::callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  return callFunction(func, {lhs, rhs});
}

ArgumentPtr LogExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*rhs == Integer(1)) {
    return Integer(0).clone();
  }

  if (*lhs == E()) {
    return callFunction(Ln(), {rhs});
  }

  return {};
}

ArgumentPtr LogExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return std::make_shared<Integer>(1);
  }

  return {};
}

ArgumentPtr LogExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Pow>(rhsExpr->getFunction())) {
    ArgumentPtr multiplier = rhsExpr->getChildren().back();
    ArgumentPtr logExpr = makeExpr(Log(), lhs, rhsExpr->getChildren().front());
    res = makeExpr(Mul(), multiplier, logExpr);
  }
  else if (auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    ArgumentPtr multiplier = makeExpr(Div(), std::make_shared<Integer>(1), lhsExpr->getChildren().back());
    ArgumentPtr logExpr = makeExpr(Log(), lhsExpr->getChildren().front(), rhs);
    res = makeExpr(Mul(), multiplier, logExpr);
  }

  return res;
}

}
