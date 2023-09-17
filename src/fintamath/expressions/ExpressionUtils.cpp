#include "fintamath/expressions/ExpressionUtils.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Complex.hpp"
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

std::string operatorChildToString(const IOperator &oper, const ArgumentPtr &child) {
  std::string childStr = child->toString();
  std::shared_ptr<IOperator> childOper;

  if (const auto childExpr = cast<IExpression>(child)) {
    childOper = cast<IOperator>(childExpr->getOutputFunction());
  }
  else if (const auto childComplex = cast<Complex>(child)) {
    if (childComplex->real() != Integer(0)) {
      childOper = std::make_shared<Add>();
    }
    else if (childComplex->imag() != Integer(1)) {
      if (childComplex->imag() == Integer(-1)) {
        childOper = std::make_shared<Neg>();
      }
      else {
        childOper = std::make_shared<Mul>();
      }
    }
  }
  else if (childStr.front() == Neg().toString().front()) {
    childOper = std::make_shared<Neg>();
  }
  else if (is<Rational>(child)) {
    childOper = std::make_shared<Div>();
  }
  else if (is<Real>(child)) {
    if (childStr.find(Mul().toString()) != std::string::npos) {
      childOper = std::make_shared<Mul>();
    }
  }

  bool shouldPutInBrackets = false;

  if (childOper) {
    shouldPutInBrackets = oper.getOperatorPriority() == IOperator::Priority::PostfixUnary ||
                          childOper->getOperatorPriority() > oper.getOperatorPriority();

    shouldPutInBrackets = shouldPutInBrackets ||
                          (childOper->getFunctionType() == IFunction::Type::Unary
                               ? childOper->getOperatorPriority() == oper.getOperatorPriority()
                               : !oper.isAssociative());
  }

  return shouldPutInBrackets ? putInBrackets(childStr) : childStr;
}

std::string binaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::string result;

  std::string operStr = oper.toString();
  const IOperator::Priority operPriority = oper.getOperatorPriority();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  std::string lhsStr = operatorChildToString(oper, lhs);
  std::string rhsStr = operatorChildToString(oper, rhs);

  return lhsStr + operStr + rhsStr;
}

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  return oper.toString() + operatorChildToString(oper, rhs);
}

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  return operatorChildToString(oper, rhs) + oper.toString();
}

bool hasVariable(const ArgumentPtr &arg) {
  if (is<Variable>(arg)) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [](const auto &child) {
    bool res = false;

    if (hasVariable(child)) {
      res = true;
    }

    return res;
  });
}

bool hasVariable(const ArgumentPtr &arg, const Variable &var) {
  if (*arg == var) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [&var](const auto &child) {
    bool res = false;

    if (hasVariable(child, var)) {
      res = true;
    }

    return res;
  });
}

bool hasInfinity(const ArgumentPtr &arg) {
  if (isInfinity(arg)) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [](const auto &child) {
    bool res = false;

    if (hasInfinity(child)) {
      res = true;
    }

    return res;
  });
}

bool hasComplex(const ArgumentPtr &arg) {
  if (const auto num = cast<INumber>(arg); num && num->isComplex()) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  ArgumentsPtrVector children = expr->getChildren();

  return std::any_of(children.begin(), children.end(), [](const auto &child) {
    bool res = false;

    if (hasComplex(child)) {
      res = true;
    }

    return res;
  });
}

bool isInfinity(const ArgumentPtr &arg) {
  return is<Inf>(arg) || is<NegInf>(arg) || is<ComplexInf>(arg);
}

bool isNegated(const ArgumentPtr &arg) {
  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  if (is<Add>(expr->getFunction())) {
    expr = cast<IExpression>(expr->getChildren().front());

    if (!expr) {
      return false;
    }
  }

  if (is<Mul>(expr->getFunction())) {
    if (auto num = cast<INumber>(expr->getChildren().front()); num && *num < Integer(0)) {
      return true;
    }
  }

  return false;
}

std::vector<std::string> argumentVectorToStringVector(const ArgumentsPtrVector &args) {
  std::vector<std::string> argStrings(args.size());

  for (size_t i = 0; i < argStrings.size(); i++) {
    argStrings[i] = args[i].get()->toString();
  }

  return argStrings;
}

ArgumentsPtrVector argumentRefVectorToArgumentPtrVector(const ArgumentsRefVector &args) {
  ArgumentsPtrVector argsPtrVect;

  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().clone());
  }

  return argsPtrVect;
}

bool isExpression(const IMathObject &arg) {
  return is<IExpression>(arg);
}

}
