#include "fintamath/expressions/binary/LogExpression.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IBinaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/logarithms/Ln.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/E.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

using namespace detail;

LogExpression::LogExpression(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Log{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

std::string LogExpression::toString() const {
  if (*lhsChild == E{}) {
    return functionToString(Ln{}, {rhsChild});
  }

  return IBinaryExpression::toString();
}

std::shared_ptr<IFunction> LogExpression::getOutputFunction() const {
  if (*lhsChild == E{}) {
    return std::make_shared<Ln>();
  }

  return IBinaryExpression::getFunction();
}

ArgumentPtr LogExpression::approximateSimplify() const {
  if (*lhsChild == E{}) {
    const auto approxExpr = cast<LogExpression>(clone());
    approximateSimplifyChild(approxExpr->rhsChild);

    if (is<INumber>(approxExpr->rhsChild)) {
      if (const auto res = cast<INumber>(approxExpr->IBinaryExpression::approximateSimplify())) {
        return res;
      }
    }

    return approxExpr->simplify();
  }

  return IBinaryExpression::approximateSimplify();
}

ArgumentPtr LogExpression::setPrecision(const unsigned precision, const Integer &maxInt) const {
  if (*lhsChild == E{}) {
    const auto approxExpr = cast<LogExpression>(clone());
    setPrecisionChild(approxExpr->rhsChild, precision, maxInt);
    return approxExpr->simplify();
  }

  return IBinaryExpression::setPrecision(precision, maxInt);
}

LogExpression::SimplifyFunctionVector LogExpression::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &LogExpression::powSimplify,
  };
  return simplifyFunctions;
}

LogExpression::SimplifyFunctionVector LogExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &LogExpression::constSimplify,
      &LogExpression::powSimplify,
      &LogExpression::equalSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr LogExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if ((*lhs == Integer(0) || isMulInfinity(lhs)) &&
      (*rhs == Integer(0) || isMulInfinity(rhs))) {

    return Undefined{}.clone();
  }

  if (*rhs == Integer(1) && !containsInfinity(lhs)) {
    return Integer(0).clone();
  }

  if (*lhs == E{}) {
    if (isInfinity(rhs)) {
      return Inf{}.clone();
    }

    return callFunction(Ln{}, {rhs});
  }

  return {};
}

ArgumentPtr LogExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs && !containsInfinity(lhs)) {
    return Integer(1).clone();
  }

  return {};
}

ArgumentPtr LogExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  ArgumentPtr res;

  if (const auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Pow>(rhsExpr->getFunction())) {
    ArgumentPtr multiplier = rhsExpr->getChildren().back();
    ArgumentPtr logExprChild = logExpr(lhs, rhsExpr->getChildren().front());
    res = mulExpr(std::move(multiplier), std::move(logExprChild));
  }
  else if (const auto lhsExpr = cast<IExpression>(lhs); lhsExpr && is<Pow>(lhsExpr->getFunction())) {
    ArgumentPtr multiplier = divExpr(Integer(1).clone(), lhsExpr->getChildren().back());
    ArgumentPtr logExprChild = logExpr(lhsExpr->getChildren().front(), rhs);
    res = mulExpr(std::move(multiplier), std::move(logExprChild));
  }

  return res;
}

}
