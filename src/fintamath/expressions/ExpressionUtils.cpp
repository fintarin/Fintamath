#include "fintamath/expressions/ExpressionUtils.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/numbers/Complex.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath::detail {

const ArgumentPtr one = Integer(1).clone();

bool isExpression(const IMathObject &arg) {
  return is<IExpression>(arg);
}

bool isInfinity(const ArgumentPtr &arg) {
  return is<Inf>(arg) || is<NegInf>(arg) || is<ComplexInf>(arg);
}

bool isMulInfinity(const ArgumentPtr &arg) {
  auto [rate, value] = splitMulExpr(arg);
  return isInfinity(rate) || isInfinity(value);
}

bool isNegated(const ArgumentPtr &arg) {
  if (isNegativeNumber(arg)) {
    return true;
  }

  const auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  if (is<Add>(expr->getFunction()) || is<Div>(expr->getFunction())) {
    return isNegated(expr->getChildren().front());
  }

  if (is<Mul>(expr->getFunction())) {
    return isNegativeNumber(expr->getChildren().front());
  }

  return false;
}

bool isNegativeNumber(const ArgumentPtr &arg) {
  const auto argNum = cast<INumber>(arg);
  return argNum && *argNum < Integer(0);
}

bool isComplexNumber(const ArgumentPtr &arg) {
  const auto num = cast<INumber>(arg);
  return num && num->isComplex();
}

bool containsIf(const ArgumentPtr &arg, const std::function<bool(const ArgumentPtr &)> &comp) {
  if (comp(arg)) {
    return true;
  }

  const auto expr = cast<IExpression>(arg);
  if (!expr) {
    return false;
  }

  const ArgumentPtrVector &children = expr->getChildren();

  return stdr::any_of(children, [&comp](const auto &child) {
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
    return isComplexNumber(compArg);
  });
}

std::pair<ArgumentPtr, ArgumentPtr> splitMulExpr(const ArgumentPtr &inChild, const bool checkVariables) {
  const auto mulExprChild = cast<IExpression>(inChild);

  if (!mulExprChild || !is<Mul>(mulExprChild->getFunction())) {
    return {one, inChild};
  }

  const ArgumentPtrVector &mulExprChildren = mulExprChild->getChildren();
  size_t i = 0;

  if (checkVariables) {
    for (; i < mulExprChildren.size(); i++) {
      if (containsVariable(mulExprChildren[i])) {
        break;
      }
    }
  }
  else {
    for (; i < mulExprChildren.size(); i++) {
      if (!is<INumber>(mulExprChildren[i])) {
        break;
      }
    }
  }

  ArgumentPtr rate = makePolynom(Mul{},
                                 ArgumentPtrVector(mulExprChildren.begin(),
                                                   mulExprChildren.begin() + static_cast<ptrdiff_t>(i)));
  ArgumentPtr value = makePolynom(Mul{},
                                  ArgumentPtrVector(mulExprChildren.begin() + static_cast<ptrdiff_t>(i),
                                                    mulExprChildren.end()));

  if (!rate) {
    rate = one;
  }

  if (!value) {
    value = checkVariables ? one : inChild;
  }

  return {rate, value};
}

std::pair<ArgumentPtr, ArgumentPtr> splitPowExpr(const ArgumentPtr &rhs) {
  if (const auto &powExpr = cast<IExpression>(rhs); powExpr && is<Pow>(powExpr->getFunction())) {
    const ArgumentPtrVector &powExprChildren = powExpr->getChildren();
    return {powExprChildren[0], powExprChildren[1]};
  }

  return {rhs, one};
}

std::pair<ArgumentPtr, ArgumentPtr> splitRational(const ArgumentPtr &arg) {
  if (const auto rat = cast<Rational>(arg)) {
    return {rat->numerator().clone(), rat->denominator().clone()};
  }

  if (const auto complex = cast<Complex>(arg)) {
    ArgumentPtr reNumerator;
    ArgumentPtr imNumerator;
    Integer denominator = 1;

    const auto *reRat = cast<Rational>(&complex->real());
    const auto *imRat = cast<Rational>(&complex->imag());

    if (reRat && imRat) {
      denominator = lcm(reRat->denominator(), imRat->denominator());
      reNumerator = (denominator / reRat->denominator() * reRat->numerator()).clone();
      imNumerator = (denominator / imRat->denominator() * imRat->numerator()).clone();
    }
    else if (reRat) {
      denominator = reRat->denominator();
      reNumerator = reRat->numerator().clone();
      imNumerator = complex->imag() * denominator;
    }
    else if (imRat) {
      denominator = imRat->denominator();
      reNumerator = complex->real() * denominator;
      imNumerator = imRat->numerator().clone();
    }

    const auto reNumeratorNum = cast<INumber>(reNumerator);
    const auto imNumeratorNum = cast<INumber>(imNumerator);

    if (denominator != 1 && reNumeratorNum && imNumeratorNum) {
      return {Complex(*reNumeratorNum, *imNumeratorNum).clone(), denominator.clone()};
    }
  }

  return {arg, Integer(1).clone()};
}

ArgumentPtr negate(const ArgumentPtr &arg) {
  if (const auto expr = cast<IExpression>(arg)) {
    if (is<Add>(expr->getFunction())) {
      auto negChildrenView =
          expr->getChildren() |
          stdv::transform([](const ArgumentPtr &child) {
            return negate(child);
          });
      return makePolynom(Add{}, ArgumentPtrVector(negChildrenView.begin(), negChildrenView.end())); // TODO: use C++23 stdv::to
    }

    if (is<Mul>(expr->getFunction())) {
      if (const auto firstChildNum = cast<INumber>(expr->getChildren().front())) {
        if (*firstChildNum == Integer(-1)) {
          ArgumentPtrVector negChildren(expr->getChildren().begin() + 1, expr->getChildren().end());
          return makePolynom(Mul(), std::move(negChildren));
        }

        ArgumentPtrVector negChildren = expr->getChildren();
        negChildren.front() = (*firstChildNum) * Integer(-1);
        return makePolynom(Mul(), std::move(negChildren));
      }
    }
  }
  else if (const auto arithm = cast<IArithmetic>(arg)) {
    return (*arithm) * Integer(-1);
  }

  return mulExpr(Integer(-1).clone(), arg);
}

ArgumentPtr makePolynom(const IFunction &func, ArgumentPtrVector &&args) {
  if (args.empty()) {
    return {};
  }

  if (args.size() == 1) {
    return args.front();
  }

  return makeExpr(func, std::move(args));
}

ArgumentPtr makePolynom(const IFunction &func, const ArgumentPtrVector &args) {
  return makePolynom(func, ArgumentPtrVector(args));
}

ArgumentPtrVector getPolynomChildren(const IFunction &func, const ArgumentPtr &arg) {
  if (const auto expr = cast<IExpression>(arg); expr && *expr->getFunction() == func) {
    return expr->getChildren();
  }

  return {arg};
}

std::vector<std::string> argumentVectorToStringVector(const ArgumentPtrVector &args) {
  std::vector<std::string> argStrings(args.size());

  for (const auto i : stdv::iota(0U, argStrings.size())) {
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
  else if (childStr.front() == Neg{}.toString().front()) {
    childOper = std::make_shared<Neg>();
  }
  else if (is<Rational>(child)) {
    childOper = std::make_shared<Div>();
  }
  else if (is<Real>(child)) {
    if (childStr.find(Mul{}.toString()) != std::string::npos) {
      childOper = std::make_shared<Mul>();
    }
  }

  bool shouldPutInBrackets = false;

  if (childOper) {
    if (oper.getPriority() == IOperator::Priority::PostfixUnary) {
      shouldPutInBrackets = true;
    }
    else if (childOper->getArgumentClasses().size() == 1) {
      shouldPutInBrackets = childOper->getPriority() >= oper.getPriority();
    }
    else {
      shouldPutInBrackets = childOper->getPriority() > oper.getPriority() ||
                            !oper.isAssociative();
    }
  }

  return shouldPutInBrackets ? putInBrackets(childStr) : childStr;
}

std::string binaryOperatorToString(const IOperator &oper, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::string operStr = oper.toString();
  const IOperator::Priority operPriority = oper.getPriority();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  const std::string lhsStr = operatorChildToString(oper, lhs);
  const std::string rhsStr = operatorChildToString(oper, rhs);

  return lhsStr + operStr + rhsStr;
}

std::string prefixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  return oper.toString() + operatorChildToString(oper, rhs);
}

std::string postfixUnaryOperatorToString(const IOperator &oper, const ArgumentPtr &rhs) {
  return operatorChildToString(oper, rhs) + oper.toString();
}

}
