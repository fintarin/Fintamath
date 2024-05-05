#include "fintamath/expressions/binary/LogExpr.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
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

FINTAMATH_CLASS_IMPLEMENTATION(LogExpr)

using namespace detail;

LogExpr::LogExpr(ArgumentPtr inLhsChild, ArgumentPtr inRhsChild)
    : IBinaryExpressionCRTP(Log{}, std::move(inLhsChild), std::move(inRhsChild)) {
}

std::string LogExpr::toString() const {
  if (*lhsChild == E{}) {
    return functionToString(Ln{}, {rhsChild});
  }

  return IBinaryExpression::toString();
}

const std::shared_ptr<IFunction> &LogExpr::getOutputFunction() const {
  static const std::shared_ptr<IFunction> ln = std::make_shared<Ln>();

  if (*lhsChild == E{}) {
    return ln;
  }

  return IBinaryExpression::getFunction();
}

ArgumentPtr LogExpr::approximate(const bool isTranformOverriden) const {
  // TODO!!!
  // if (*lhsChild == E{}) {
  //   const auto approxExpr = cast<LogExpr>(clone());
  //   approximateChild(approxExpr->rhsChild);

  //   if (const auto res = cast<INumber>(approxExpr->IBinaryExpression::approximate())) {
  //     return res;
  //   }

  //   simplifyChild(approxExpr); // TODO! solveChild()
  //   approxExpr->changeState(State::Approximate);
  //   return approxExpr;
  // }

  return IBinaryExpression::approximate(isTranformOverriden);
}

LogExpr::SimplifyFunctionVector LogExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &LogExpr::powSimplify,
  };
  return simplifyFunctions;
}

LogExpr::SimplifyFunctionVector LogExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &LogExpr::constSimplify,
      &LogExpr::powSimplify,
      &LogExpr::equalSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr LogExpr::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
  }

  return {};
}

ArgumentPtr LogExpr::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs && !containsInfinity(lhs)) {
    return Integer(1).clone();
  }

  return {};
}

ArgumentPtr LogExpr::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
