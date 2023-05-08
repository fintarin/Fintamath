#include "fintamath/expressions/binary/LogExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
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
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

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

LogExpression::SimplifyFunctionsVector LogExpression::getFunctionsForSimplify() const {
  static const LogExpression::SimplifyFunctionsVector simplifyFunctions = {
      &LogExpression::numbersSimplify, //
      &LogExpression::equalSimplify,   //
      &LogExpression::powSimplify,     //
  };
  return simplifyFunctions;
}

ArgumentPtr LogExpression::numbersSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == ONE) {
    throw UndefinedFunctionException(Log().toString(), {lhs->toString(), rhs->toString()});
  }

  if (*lhs == E()) {
    return callFunction(Ln(), {rhs});
  }

  if (Log().doArgsMatch({*lhs, *rhs})) {
    if (*lhs == TWO) {
      return callFunction(Lb(), {rhs});
    }

    if (*lhs == TEN) {
      return callFunction(Lg(), {rhs});
    }

    return callFunction(Log(), {lhs, rhs});
  }

  return {};
}

ArgumentPtr LogExpression::equalSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return ONE.clone();
  }

  return {};
}

ArgumentPtr LogExpression::powSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Pow>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(), {rhsExpr->getChildren().back(),
                                          makeRawFunctionExpression(Log(), {lhs, rhsExpr->getChildren().front()})});
  }

  if (auto rhsExpr = cast<IExpression>(rhs); rhsExpr && is<Pow>(rhsExpr->getFunction())) {
    return makeFunctionExpression(Mul(),
                                  {makeRawFunctionExpression(Div(), {ONE.clone(), rhsExpr->getChildren().back()}),
                                   makeRawFunctionExpression(Log(), {lhs, rhsExpr->getChildren().front()})});
  }

  return {};
}

}
