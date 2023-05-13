#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/powers/Pow.hpp"

namespace fintamath {

std::string putInBrackets(const std::string &str) {
  return '(' + str + ')';
}

std::string putInSpaces(const std::string &str) {
  return ' ' + str + ' ';
}

std::string functionToString(const IFunction &func, const ArgumentsPtrVector &args) {
  static const std::string delimiter = ", ";

  std::string result = func.toString() + "(";

  for (const auto &arg : args) {
    result += arg->toString() + delimiter;
  }

  result = result.substr(0, result.length() - delimiter.length()) + ")";

  return result;
}

std::string binaryOperatorToString(const IOperator &oper, const ArgumentsPtrVector &values) {
  std::string result;

  std::string operStr = oper.toString();
  IOperator::Priority operPriority = oper.getOperatorPriority();
  bool operIsAssociative = oper.isAssociative();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  for (size_t i = 0; i < values.size(); i++) {
    const ArgumentPtr &child = values[i];
    std::string childStr = child->toString();

    std::shared_ptr<const IOperator> childOper;
    if (const auto childExpr = cast<IExpression>(child)) {
      childOper = cast<IOperator>(childExpr->getFunction());
    }
    else if (childStr.find(Div().toString()) != std::string::npos) {
      childOper = cast<IOperator>(Div().clone());
    }
    else if (childStr.find(Pow().toString()) != std::string::npos) {
      childOper = cast<IOperator>(Pow().clone());
    }

    bool shouldPutInBrackets = false;
    if (childOper) {
      IOperator::Priority childOperPriority = childOper->getOperatorPriority();

      if (childOperPriority > operPriority ||
          (childOperPriority == operPriority && !operIsAssociative && (*childOper != oper || i > 0))) {
        shouldPutInBrackets = true;
      }
    }

    if (shouldPutInBrackets) {
      result += putInBrackets(childStr);
    }
    else {
      result += childStr;
    }

    result += operStr;
  }

  result = result.substr(0, result.length() - operStr.length());

  return result;
}

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  std::string result = oper.toString();

  if (const auto childExpr = cast<IExpression>(rhs)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      return result + putInBrackets(rhs->toString());
    }
  }

  return result + rhs->toString();
}

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  std::string result = rhs->toString();

  if (const auto child = cast<IExpression>(rhs)) {
    if (const auto childOper = cast<IOperator>(child->getFunction())) {
      if (IOperator::Priority priority = childOper->getOperatorPriority();
          priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(rhs); comp && *comp < Integer(0)) {
    return putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

bool hasVariables(const std::shared_ptr<const IExpression> &expr) {
  for (const auto &child : expr->getChildren()) {
    if (is<Variable>(child)) {
      return true;
    }

    if (const auto childExpr = cast<IExpression>(child)) {
      if (hasVariables(childExpr)) {
        return true;
      }
    }
  }

  return false;
}

bool hasVariable(const std::shared_ptr<const IExpression> &expr, const Variable &var) {
  for (const auto &child : expr->getChildren()) {
    if (const auto childVar = cast<Variable>(child); childVar && *childVar == var) {
      return true;
    }

    if (const auto childExpr = cast<IExpression>(child); childExpr && hasVariable(childExpr, var)) {
      return true;
    }
  }

  return false;
}

}