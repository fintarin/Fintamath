#include "fintamath/expressions/polynomial/AddExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/functions/powers/Sqr.hpp"
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

AddExpression::AddExpression(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Add(), std::move(inChildren)) {
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

std::strong_ordering AddExpression::compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (lhsExpr &&
      is<Div>(lhsExpr->getFunction()) &&
      (!rhsExpr || !is<Div>(rhsExpr->getFunction()))) {

    return std::strong_ordering::less;
  }

  if (rhsExpr &&
      is<Div>(rhsExpr->getFunction()) &&
      (!lhsExpr || !is<Div>(lhsExpr->getFunction()))) {

    return std::strong_ordering::greater;
  }

  return IPolynomExpression::compare(lhs, rhs);
}

AddExpression::SimplifyFunctionVector AddExpression::getFunctionsForPreSimplify() const {
  static const AddExpression::SimplifyFunctionVector simplifyFunctions = {
      &AddExpression::divSimplify,
      &AddExpression::constSimplify,
      &AddExpression::mulSimplify,
      &AddExpression::logSimplify,
      &AddExpression::mulLogSimplify,
  };
  return simplifyFunctions;
}

AddExpression::SimplifyFunctionVector AddExpression::getFunctionsForPostSimplify() const {
  static const AddExpression::SimplifyFunctionVector simplifyFunctions = {
      &AddExpression::constSimplify,
      &AddExpression::mulSimplify,
      &AddExpression::logSimplify,
      &AddExpression::mulLogSimplify,
      &AddExpression::trigSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AddExpression::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == Integer(0)) {
    return rhs;
  }

  if (*rhs == Integer(0)) {
    return lhs;
  }

  if ((is<NegInf>(lhs) || is<ComplexInf>(lhs)) &&
      (is<Inf>(rhs) || is<ComplexInf>(rhs))) {

    return Undefined().clone();
  }

  if ((is<Inf>(lhs) && is<Inf>(rhs)) ||
      (is<NegInf>(lhs) && is<NegInf>(rhs))) {

    return lhs;
  }

  if (isInfinity(lhs) && !containsInfinity(rhs)) {
    return lhs;
  }

  if (isInfinity(rhs) && !containsInfinity(lhs)) {
    return rhs;
  }

  return {};
}

ArgumentPtr AddExpression::logSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr ||
      !is<Log>(lhsExpr->getFunction()) || !is<Log>(rhsExpr->getFunction())) {
    return {};
  }

  const ArgumentPtrVector &lhsChildren = lhsExpr->getChildren();
  const ArgumentPtrVector &rhsChildren = rhsExpr->getChildren();

  if (*lhsChildren.front() == *rhsChildren.front()) {
    ArgumentPtr logLhs = lhsChildren.front();
    ArgumentPtr logRhs = mulExpr(lhsChildren.back(), rhsChildren.back());
    ArgumentPtr res = logExpr(logLhs, logRhs);
    return res;
  }

  return {};
}

ArgumentPtr AddExpression::mulLogSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr) {
    return {};
  }

  if (is<Mul>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    const ArgumentPtrVector &lhsExprChildren = lhsExpr->getChildren();
    const ArgumentPtrVector &rhsExprChildren = rhsExpr->getChildren();

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
          return logExpr(logLhs, logRhs);
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

  const ArgumentPtrVector &mulExprChildren = mulExprChild->getChildren();
  std::vector<size_t> logChildrenIndexes = findLogarithms(mulExprChildren);

  for (size_t i : logChildrenIndexes) {
    auto logChild = cast<IExpression>(mulExprChildren[i]);

    if (*logChild->getChildren().front() == *logExprChild->getChildren().front()) {
      logChild = mulToLogarithm(mulExprChildren, i);

      ArgumentPtr logLhs = logExprChild->getChildren().front();
      ArgumentPtr logRhs = mulExpr(logExprChild->getChildren().back(), logChild->getChildren().back());
      return logExpr(logLhs, logRhs);
    }
  }

  return {};
}

std::vector<size_t> AddExpression::findLogarithms(const ArgumentPtrVector &children) {
  std::vector<size_t> indexes;

  for (const auto i : stdv::iota(0U, children.size())) {
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

  const ArgumentPtr powRate = mulChildren.size() > 1 ? mulExpr(std::move(mulChildren)) : mulChildren.front();
  const ArgumentPtr logRhsChild = powExpr(logExprChild->getChildren().back(), powRate);

  return cast<IExpression>(logExpr(logExprChild->getChildren().front(), logRhsChild));
}

ArgumentPtr AddExpression::mulSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  {
    auto [lhsChildRate, lhsChildValue] = splitMulExpr(lhs, false);
    auto [rhsChildRate, rhsChildValue] = splitMulExpr(rhs, false);

    if (*lhsChildValue == *rhsChildValue) {
      return mulExpr(addExpr(lhsChildRate, rhsChildRate), lhsChildValue);
    }
  }

  {
    auto [lhsChildRate, lhsChildValue] = splitMulExpr(lhs);
    auto [rhsChildRate, rhsChildValue] = splitMulExpr(rhs);

    if (*lhsChildValue == *rhsChildValue && *lhsChildValue != Integer(1)) {
      return mulExpr(addExpr(lhsChildRate, rhsChildRate), lhsChildValue);
    }
  }

  return {};
}

ArgumentPtr AddExpression::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (const auto rhsRat = cast<Rational>(rhs)) {
    rhsExpr = cast<IExpression>(divExpr(rhsRat->numerator(), rhsRat->denominator()));
  }

  ArgumentPtr res;

  if (rhsExpr && is<Div>(rhsExpr->getFunction()) && containsInfinity(rhsExpr)) {
    return {};
  }

  if (lhsExpr && rhsExpr &&
      is<Div>(lhsExpr->getFunction()) && is<Div>(rhsExpr->getFunction())) {

    if (*lhsExpr->getChildren().back() == *rhsExpr->getChildren().back()) {
      const ArgumentPtr &lhsNumerator = lhsExpr->getChildren().front();
      const ArgumentPtr &rhsNumerator = rhsExpr->getChildren().front();
      const ArgumentPtr &rhsDenominator = rhsExpr->getChildren().back();

      ArgumentPtr numerator = addExpr(lhsNumerator, rhsNumerator);
      ArgumentPtr denominator = rhsDenominator;
      res = divExpr(numerator, denominator);
    }
    else {
      const ArgumentPtr &lhsNumerator = lhsExpr->getChildren().front();
      const ArgumentPtr &rhsNumerator = rhsExpr->getChildren().front();
      const ArgumentPtr &lhsDenominator = lhsExpr->getChildren().back();
      const ArgumentPtr &rhsDenominator = rhsExpr->getChildren().back();

      ArgumentPtr lhsNumeratorMulRhsDenominator = mulExpr(lhsNumerator, rhsDenominator);
      ArgumentPtr rhsNumeratorMulLhsDenominator = mulExpr(rhsNumerator, lhsDenominator);

      ArgumentPtr numerator = addExpr(lhsNumeratorMulRhsDenominator, rhsNumeratorMulLhsDenominator);
      ArgumentPtr denominator = mulExpr(lhsDenominator, rhsDenominator);
      res = divExpr(numerator, denominator);
    }
  }
  else if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    const ArgumentPtr &rhsNumerator = rhsExpr->getChildren().front();
    const ArgumentPtr &rhsDenominator = rhsExpr->getChildren().back();

    ArgumentPtr lhsMulRhsDenominator = mulExpr(lhs, rhsDenominator);

    ArgumentPtr numerator = addExpr(lhsMulRhsDenominator, rhsNumerator);
    ArgumentPtr denominator = rhsDenominator;
    res = divExpr(numerator, denominator);
  }

  return res;
}

ArgumentPtr AddExpression::trigSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsMulRate, lhsMulValue] = splitMulExpr(lhs, false);
  auto [rhsMulRate, rhsMulValue] = splitMulExpr(rhs, false);

  auto [lhsPowBase, lhsPowRate] = splitPowExpr(lhsMulValue);
  auto [rhsPowBase, rhsPowRate] = splitPowExpr(rhsMulValue);

  auto lhsPowBaseExpr = cast<IExpression>(lhsPowBase);
  auto rhsPowBaseExpr = cast<IExpression>(rhsPowBase);

  if (!lhsPowBaseExpr || *lhsPowRate != Integer(2)) {
    return {};
  }

  if (containsInfinity(lhsPowBase) || containsInfinity(rhsPowBase)) {
    return {};
  }

  auto lhsPowBaseChild = lhsPowBaseExpr->getChildren().front();

  auto lhsMulRateNum = cast<INumber>(lhsMulRate);

  if (rhsPowBaseExpr && *rhsPowRate == Integer(2)) {
    if (!is<Sin>(lhsPowBaseExpr->getFunction()) || !is<Cos>(rhsPowBaseExpr->getFunction())) {
      return {};
    }

    auto rhsPowBaseChild = rhsPowBaseExpr->getChildren().front();

    if (*lhsPowBaseChild != *rhsPowBaseChild) {
      return {};
    }

    if (*lhsMulRate == *rhsMulRate) {
      return lhsMulRate;
    }

    auto rhsMulRateNum = cast<INumber>(rhsMulRate);

    if (lhsMulRateNum && rhsMulRateNum && *(*lhsMulRateNum + *rhsMulRateNum) == Integer(0)) {
      ArgumentPtr res = cosExpr(
          mulExpr(
              lhsPowBaseExpr->getChildren().front(),
              Integer(2).clone()));

      return mulExpr(rhsMulRateNum, res);
    }

    return {};
  }

  auto rhsNum = cast<INumber>(rhs);

  if (lhsMulRateNum && rhsNum && *(*lhsMulRateNum + *rhsNum) == Integer(0)) {
    ArgumentPtr res = lhsPowBaseExpr->getChildren().front();

    if (is<Sin>(lhsPowBaseExpr->getFunction())) {
      res = cosExpr(res);
    }
    else if (is<Cos>(lhsPowBaseExpr->getFunction())) {
      res = sinExpr(res);
    }
    else {
      return {};
    }

    return mulExpr(rhsNum, sqrExpr(res));
  }

  return {};
}

}
