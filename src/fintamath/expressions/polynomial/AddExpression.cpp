#include "fintamath/expressions/polynomial/AddExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/trigonometry/Cos.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

AddExpression::AddExpression(const ArgumentPtrVector &inChildren)
    : IPolynomExpressionCRTP(Add(), inChildren) {
}

std::string AddExpression::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = operatorChildToString(oper, inChild);
  bool isChildNegated = false;

  if (result.size() > 1 &&
      result.front() == Neg().toString().front()) {

    isChildNegated = true;
    result = result.substr(1, result.size() - 1);
  }

  std::string funcStr;

  if (isChildNegated) {
    funcStr = Sub().toString();
  }
  else if (prevChild) {
    funcStr = oper.toString();
  }

  if (!funcStr.empty()) {
    if (prevChild) {
      funcStr = putInSpaces(funcStr);
    }

    result = funcStr + result;
  }

  return result;
}

int AddExpression::comparator(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr &&
      is<Div>(lhsExpr->getFunction()) &&
      (!rhsExpr || !is<Div>(rhsExpr->getFunction()))) {
    return 1;
  }

  if (rhsExpr &&
      is<Div>(rhsExpr->getFunction()) &&
      (!lhsExpr || !is<Div>(lhsExpr->getFunction()))) {
    return -1;
  }

  return IPolynomExpression::comparator(lhs, rhs);
}

AddExpression::SimplifyFunctionVector AddExpression::getFunctionsForPreSimplify() const {
  static const AddExpression::SimplifyFunctionVector simplifyFunctions = {
      &AddExpression::callFunctionSimplify,
      &AddExpression::sumSimplify,
      &AddExpression::constSimplify,
      &AddExpression::powSimplify,
      &AddExpression::logSimplify,
      &AddExpression::mulLogSimplify,
  };
  return simplifyFunctions;
}

AddExpression::SimplifyFunctionVector AddExpression::getFunctionsForPostSimplify() const {
  static const AddExpression::SimplifyFunctionVector simplifyFunctions = {
      &AddExpression::constSimplify,
      &AddExpression::powSimplify,
      &AddExpression::logSimplify,
      &AddExpression::mulLogSimplify,
      &AddExpression::trigSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AddExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == Integer(0)) {
    return rhsChild;
  }

  if (*rhsChild == Integer(0)) {
    return lhsChild;
  }

  if ((is<NegInf>(lhsChild) || is<ComplexInf>(lhsChild)) &&
      (is<Inf>(rhsChild) || is<ComplexInf>(rhsChild))) {

    return Undefined().clone();
  }

  if ((is<Inf>(lhsChild) && is<Inf>(rhsChild)) ||
      (is<NegInf>(lhsChild) && is<NegInf>(rhsChild))) {

    return lhsChild;
  }

  if ((is<Inf>(lhsChild) || is<NegInf>(lhsChild) || is<ComplexInf>(lhsChild)) &&
      !hasInfinity(cast<IExpression>(rhsChild))) {

    return lhsChild;
  }

  if ((is<Inf>(rhsChild) || is<NegInf>(rhsChild) || is<ComplexInf>(rhsChild)) &&
      !hasInfinity(cast<IExpression>(lhsChild))) {

    return rhsChild;
  }

  return {};
}

ArgumentPtr AddExpression::callFunctionSimplify(const IFunction &func, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  return callFunction(func, {lhsChild, rhsChild});
}

ArgumentPtr AddExpression::logSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr ||
      !is<Log>(lhsExpr->getFunction()) || !is<Log>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentPtrVector rhsChildren = rhsExpr->getChildren();

  if (*lhsChildren.front() == *rhsChildren.front()) {
    ArgumentPtr logLhs = lhsChildren.front();
    ArgumentPtr logRhs = mulExpr(lhsChildren.back(), rhsChildren.back());
    ArgumentPtr res = logExpr(logLhs, logRhs);
    return res;
  }

  return {};
}

ArgumentPtr AddExpression::mulLogSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr) {
    return {};
  }

  if (is<Mul>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    ArgumentPtrVector lhsExprChildren = lhsExpr->getChildren();
    ArgumentPtrVector rhsExprChildren = rhsExpr->getChildren();

    std::vector<size_t> lhsLogChildrenIndexes = findLogarithms(lhsExprChildren);
    std::vector<size_t> rhsLogChildrenIndexes = findLogarithms(rhsExprChildren);

    for (size_t i : lhsLogChildrenIndexes) {
      auto lhsLogChild = cast<IExpression>(lhsExprChildren[i]);

      for (size_t j : rhsLogChildrenIndexes) {
        auto rhsLogChild = cast<IExpression>(rhsExprChildren[j]);

        if (*lhsLogChild->getChildren().front() == *rhsLogChild->getChildren().front()) {
          lhsLogChild = cast<IExpression>(mulToLogarithm(lhsExprChildren, i));
          rhsLogChild = cast<IExpression>(mulToLogarithm(rhsExprChildren, j));

          ArgumentPtr logLhs = lhsLogChild->getChildren().front();
          ArgumentPtr logRhs = mulExpr(lhsLogChild->getChildren().back(), rhsLogChild->getChildren().back());
          ArgumentPtr res = logExpr(logLhs, logRhs);
          return res;
        }
      }
    }
  }

  std::shared_ptr<const IExpression> mulExprChild;
  std::shared_ptr<const IExpression> logExprChild;

  if (is<Mul>(lhsExpr->getFunction()) && is<Log>(rhsExpr->getFunction())) {
    mulExprChild = lhsExpr;
    logExprChild = rhsExpr;
  }
  else if (is<Log>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    mulExprChild = rhsExpr;
    logExprChild = lhsExpr;
  }
  else {
    return {};
  }

  ArgumentPtrVector mulExprChildren = mulExprChild->getChildren();
  std::vector<size_t> logChildrenIndexes = findLogarithms(mulExprChildren);

  for (size_t i : logChildrenIndexes) {
    auto logChild = cast<IExpression>(mulExprChildren[i]);

    if (*logChild->getChildren().front() == *logExprChild->getChildren().front()) {
      logChild = mulToLogarithm(mulExprChildren, i);

      ArgumentPtr logLhs = logExprChild->getChildren().front();
      ArgumentPtr logRhs = mulExpr(logExprChild->getChildren().back(), logChild->getChildren().back());
      ArgumentPtr res = logExpr(logLhs, logRhs);
      return res;
    }
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> AddExpression::getRateValuePair(const ArgumentPtr &inChild) {
  ArgumentPtr rate;
  ArgumentPtr value;

  if (const auto mulExprChild = cast<IExpression>(inChild);
      mulExprChild && is<Mul>(mulExprChild->getFunction())) {

    const ArgumentPtrVector mulExprChildren = mulExprChild->getChildren();

    if (is<INumber>(mulExprChildren.front())) {
      rate = mulExprChildren.front();

      if (mulExprChildren.size() == 2) {
        value = mulExprChildren[1];
      }
      else {
        value = mulExpr(ArgumentPtrVector(mulExprChildren.begin() + 1, mulExprChildren.end()));
      }
    }
  }

  if (!rate || !value) {
    rate = Integer(1).clone();
    value = inChild;
  }

  return {rate, value};
}

ArgumentPtr AddExpression::addRatesToValue(const ArgumentPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = addExpr(rates);
  ArgumentPtr res = mulExpr(ratesSum, value);
  return res;
}

std::vector<size_t> AddExpression::findLogarithms(const ArgumentPtrVector &children) {
  std::vector<size_t> indexes;

  for (size_t i = 0; i < children.size(); i++) {
    if (const auto childExpr = cast<const IExpression>(children[i]);
        childExpr && is<Log>(childExpr->getFunction())) {

      indexes.emplace_back(i);
    }
  }

  return indexes;
}

std::shared_ptr<const IExpression> AddExpression::mulToLogarithm(const ArgumentPtrVector &children, size_t i) {
  ArgumentPtrVector mulChildren = children;
  auto logExprChild = cast<const IExpression>(mulChildren[i]);

  mulChildren.erase(mulChildren.begin() + ptrdiff_t(i));

  const ArgumentPtr powRate = mulChildren.size() > 1 ? mulExpr(mulChildren) : mulChildren.front();
  const ArgumentPtr logRhsChild = powExpr(logExprChild->getChildren().back(), powRate);

  return cast<IExpression>(logExpr(logExprChild->getChildren().front(), logRhsChild));
}

ArgumentPtr AddExpression::powSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                       const ArgumentPtr &rhsChild) {

  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

ArgumentPtr AddExpression::sumSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (const auto rhsRat = cast<Rational>(rhsChild)) {
    rhsExpr = cast<IExpression>(divExpr(rhsRat->numerator(), rhsRat->denominator()));
  }

  ArgumentPtr res;

  if (lhsExpr && rhsExpr &&
      is<Div>(lhsExpr->getFunction()) && is<Div>(rhsExpr->getFunction())) {

    if (*lhsExpr->getChildren().back() == *rhsExpr->getChildren().back()) {
      ArgumentPtr lhsNumerator = lhsExpr->getChildren().front();
      ArgumentPtr rhsNumerator = rhsExpr->getChildren().front();
      ArgumentPtr rhsDenominator = rhsExpr->getChildren().back();

      ArgumentPtr numerator = addExpr(lhsNumerator, rhsNumerator);
      ArgumentPtr denominator = rhsDenominator;
      res = divExpr(numerator, denominator);
    }
    else {
      ArgumentPtr lhsNumerator = lhsExpr->getChildren().front();
      ArgumentPtr rhsNumerator = rhsExpr->getChildren().front();
      ArgumentPtr lhsDenominator = lhsExpr->getChildren().back();
      ArgumentPtr rhsDenominator = rhsExpr->getChildren().back();

      ArgumentPtr lhsNumeratorMulRhsDenominator = mulExpr(lhsNumerator, rhsDenominator);
      ArgumentPtr rhsNumeratorMulLhsDenominator = mulExpr(rhsNumerator, lhsDenominator);

      ArgumentPtr numerator = addExpr(lhsNumeratorMulRhsDenominator, rhsNumeratorMulLhsDenominator);
      ArgumentPtr denominator = mulExpr(lhsDenominator, rhsDenominator);
      res = divExpr(numerator, denominator);
    }
  }
  else if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    ArgumentPtr rhsNumerator = rhsExpr->getChildren().front();
    ArgumentPtr rhsDenominator = rhsExpr->getChildren().back();

    ArgumentPtr lhsMulRhsDenominator = mulExpr(lhsChild, rhsDenominator);

    ArgumentPtr numerator = addExpr(lhsMulRhsDenominator, rhsNumerator);
    ArgumentPtr denominator = rhsDenominator;
    res = divExpr(numerator, denominator);
  }

  return res;
}

ArgumentPtr AddExpression::trigSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (lhsExpr && rhsExpr &&
      is<Pow>(lhsExpr->getFunction()) && is<Pow>(rhsExpr->getFunction()) &&
      *lhsExpr->getChildren().back() == Integer(2) && *rhsExpr->getChildren().back() == Integer(2)) {

    auto lhsExprChildExpr = cast<IExpression>(lhsExpr->getChildren().front());
    auto rhsExprChildExpr = cast<IExpression>(rhsExpr->getChildren().front());

    if (lhsExprChildExpr && rhsExprChildExpr &&
        is<Cos>(lhsExprChildExpr->getFunction()) && is<Sin>(rhsExprChildExpr->getFunction()) &&
        *lhsExprChildExpr->getChildren().front() == *rhsExprChildExpr->getChildren().front()) {

      return Integer(1).clone();
    }
  }

  return {};
}

}
