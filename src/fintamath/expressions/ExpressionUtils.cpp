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

std::string functionToString(const IFunction &func, const ArgumentPtrVector &args) {
  static const std::string delimiter = ", ";

  std::string result = func.toString() + "(";

  for (const auto &arg : args) {
    result += arg->toString() + delimiter;
  }

  result = result.substr(0, result.size() - delimiter.size()) + ")";

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
    if (oper.getOperatorPriority() == IOperator::Priority::PostfixUnary) {
      shouldPutInBrackets = true;
    }
    else if (childOper->getFunctionType() == IFunction::Type::Unary) {
      shouldPutInBrackets = childOper->getOperatorPriority() >= oper.getOperatorPriority();
    }
    else {
      shouldPutInBrackets = childOper->getOperatorPriority() > oper.getOperatorPriority() ||
                            !oper.isAssociative();
    }
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

bool containsIf(const ArgumentPtr &arg, std::invocable<ArgumentPtr> auto comp) {
  if (comp(arg)) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  const ArgumentPtrVector &children = expr->getChildren();

  return std::ranges::any_of(children, [comp](const auto &child) {
    bool res = false;

    if (containsIf(child, comp)) {
      res = true;
    }

    return res;
  });
}

bool containsChild(const ArgumentPtr &arg, const ArgumentPtr &child) {
  return containsIf(arg, [&child](const ArgumentPtr &compArg) {
    return *compArg == *child;
  });
}

bool containsVariable(const ArgumentPtr &arg) {
  return containsIf(arg, [](const ArgumentPtr &compArg) {
    return is<Variable>(compArg);
  });
}

bool containsVariable(const ArgumentPtr &arg, const Variable &var) {
  return containsIf(arg, [&var](const ArgumentPtr &compArg) {
    return *compArg == var;
  });
}

bool containsInfinity(const ArgumentPtr &arg) {
  return containsIf(arg, [](const ArgumentPtr &compArg) {
    return isInfinity(compArg);
  });
}

bool containsComplex(const ArgumentPtr &arg) {
  return containsIf(arg, [](const ArgumentPtr &compArg) {
    const auto num = cast<INumber>(compArg);
    return num && num->isComplex();
  });
}

bool isInfinity(const ArgumentPtr &arg) {
  return is<Inf>(arg) || is<NegInf>(arg) || is<ComplexInf>(arg);
}

bool isNegated(const ArgumentPtr &arg) {
  if (isNegativeNumber(arg)) {
    return true;
  }

  auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  if (is<Add>(expr->getFunction())) {
    expr = cast<IExpression>(expr->getChildren().front());

    if (!expr || !containsVariable(expr)) {
      return false;
    }
  }

  if (is<Mul>(expr->getFunction())) {
    return isNegativeNumber(expr->getChildren().front());
  }

  return false;
}

bool isNegativeNumber(const ArgumentPtr &arg) {
  auto argNum = cast<INumber>(arg);
  return argNum && *argNum < Integer(0);
}

std::vector<std::string> argumentVectorToStringVector(const ArgumentPtrVector &args) {
  std::vector<std::string> argStrings(args.size());

  for (auto i : std::views::iota(0U, argStrings.size())) {
    argStrings[i] = args[i].get()->toString();
  }

  return argStrings;
}

ArgumentPtrVector argumentRefVectorToArgumentPtrVector(const ArgumentRefVector &args) {
  ArgumentPtrVector argsPtrVect;

  for (const auto &arg : args) {
    argsPtrVect.emplace_back(arg.get().clone());
  }

  return argsPtrVect;
}

ArgumentPtr makePolynom(const IFunction &func, const ArgumentPtrVector &args) {
  if (args.empty()) {
    return {};
  }

  if (args.size() == 1) {
    return args.front();
  }

  return makeExpr(func, args);
}

bool isExpression(const IMathObject &arg) {
  return is<IExpression>(arg);
}

}
