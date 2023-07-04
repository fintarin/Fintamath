#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

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

std::string binaryOperatorChildToString(const IOperator &oper, const ArgumentPtr &child) {
  std::string childStr = child->toString();
  std::shared_ptr<IOperator> childOper;

  if (const auto childExpr = cast<IExpression>(child)) {
    childOper = cast<IOperator>(childExpr->getOutputFunction());
  }
  else if (is<Rational>(child)) {
    childOper = std::make_shared<Div>();
  }
  else if (is<Real>(child)) {
    if (childStr.find(Mul().toString()) != std::string::npos) {
      childOper = std::make_shared<Mul>();
    }
  }

  if (childOper) {
    IOperator::Priority operPriority = oper.getOperatorPriority();
    IOperator::Priority lhsOperPriority = childOper->getOperatorPriority();

    if (lhsOperPriority > operPriority || (lhsOperPriority == operPriority && !oper.isAssociative())) {
      return putInBrackets(childStr);
    }
  }

  return childStr;
}

std::string binaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::string result;

  std::string operStr = oper.toString();
  const IOperator::Priority operPriority = oper.getOperatorPriority();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  std::string lhsStr = binaryOperatorChildToString(oper, lhs);
  std::string rhsStr = binaryOperatorChildToString(oper, rhs);

  return lhsStr + operStr + rhsStr;
}

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  std::string result = oper.toString();

  if (const auto child = cast<IExpression>(rhs)) {
    if (is<IOperator>(child->getFunction())) {
      return result + putInBrackets(rhs->toString());
    }
  }

  return result + rhs->toString();
}

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  std::string result = rhs->toString();

  if (const auto child = cast<IExpression>(rhs)) {
    if (is<IOperator>(child->getFunction())) {
      return putInBrackets(result) + oper.toString();
    }
  }

  return result + oper.toString();
}

bool hasVariables(const std::shared_ptr<const IExpression> &expr) {
  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [](const auto &child) {
    bool res = false;

    if (is<Variable>(child)) {
      res = true;
    }
    else if (const auto childExpr = cast<IExpression>(child)) {
      if (hasVariables(childExpr)) {
        res = true;
      }
    }

    return res;
  });
}

bool hasVariable(const std::shared_ptr<const IExpression> &expr, const Variable &var) {
  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [&var](const auto &child) {
    bool res = false;

    if (const auto childVar = cast<Variable>(child); childVar && *childVar == var) {
      res = true;
    }

    if (const auto childExpr = cast<IExpression>(child); childExpr && hasVariable(childExpr, var)) {
      res = true;
    }

    return res;
  });
}

std::vector<std::string> argumentVectorToStringVector(const ArgumentsPtrVector &args) {
  std::vector<std::string> argStrings(args.size());

  for (size_t i = 0; i < argStrings.size(); i++) {
    argStrings[i] = args[i].get()->toString();
  }

  return argStrings;
}

bool isExpression(const IMathObject &arg) {
  return is<IExpression>(arg);
}

}