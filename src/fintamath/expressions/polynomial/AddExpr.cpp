#include "fintamath/expressions/polynomial/AddExpr.hpp"

#include <compare>
#include <cstddef>
#include <memory>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
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
#include "fintamath/literals/constants/ComplexInf.hpp"
#include "fintamath/literals/constants/Inf.hpp"
#include "fintamath/literals/constants/NegInf.hpp"
#include "fintamath/literals/constants/Undefined.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

using namespace detail;

AddExpr::AddExpr(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Add{}, std::move(inChildren)) {
}

std::string AddExpr::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = operatorChildToString(oper, inChild);
  bool isChildNegated = false;

  if (result.size() > 1 &&
      result.front() == Neg{}.toString().front()) {

    isChildNegated = true;
    result = result.substr(1, result.size() - 1);
  }

  std::string funcStr;

  if (isChildNegated) {
    funcStr = Sub{}.toString();
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

std::strong_ordering AddExpr::compare(const ArgumentPtr &lhs, const ArgumentPtr &rhs) const {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

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

AddExpr::SimplifyFunctionVector AddExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AddExpr::divSimplify,
      &AddExpr::constSimplify,
      &AddExpr::mulSimplify,
      &AddExpr::logSimplify,
      &AddExpr::mulLogSimplify,
  };
  return simplifyFunctions;
}

AddExpr::SimplifyFunctionVector AddExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AddExpr::constSimplify,
      &AddExpr::mulSimplify,
      &AddExpr::logSimplify,
      &AddExpr::mulLogSimplify,
      &AddExpr::trigSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr AddExpr::constSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == Integer(0)) {
    return rhs;
  }

  if (*rhs == Integer(0)) {
    return lhs;
  }

  if ((is<NegInf>(lhs) || is<ComplexInf>(lhs)) &&
      (is<Inf>(rhs) || is<ComplexInf>(rhs))) {

    return Undefined{}.clone();
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

ArgumentPtr AddExpr::logSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr ||
      !is<Log>(lhsExpr->getFunction()) || !is<Log>(rhsExpr->getFunction())) {
    return {};
  }

  const ArgumentPtrVector &lhsChildren = lhsExpr->getChildren();
  const ArgumentPtrVector &rhsChildren = rhsExpr->getChildren();

  if (*lhsChildren.front() == *rhsChildren.front()) {
    ArgumentPtr logLhs = lhsChildren.front();
    ArgumentPtr logRhs = mulExpr(lhsChildren.back(), rhsChildren.back());
    ArgumentPtr res = logExpr(std::move(logLhs), std::move(logRhs));
    return res;
  }

  return {};
}

ArgumentPtr AddExpr::mulLogSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr) {
    return {};
  }

  if (is<Mul>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    const ArgumentPtrVector &lhsExprChildren = lhsExpr->getChildren();
    const ArgumentPtrVector &rhsExprChildren = rhsExpr->getChildren();

    const std::vector<size_t> lhsLogChildrenIndices = findLogarithms(lhsExprChildren);
    const std::vector<size_t> rhsLogChildrenIndices = findLogarithms(rhsExprChildren);

    for (const size_t i : lhsLogChildrenIndices) {
      auto lhsLogChild = cast<IExpression>(lhsExprChildren[i]);

      for (const size_t j : rhsLogChildrenIndices) {
        auto rhsLogChild = cast<IExpression>(rhsExprChildren[j]);

        if (*lhsLogChild->getChildren().front() == *rhsLogChild->getChildren().front()) {
          lhsLogChild = cast<IExpression>(mulToLogarithm(lhsExprChildren, i));
          rhsLogChild = cast<IExpression>(mulToLogarithm(rhsExprChildren, j));

          ArgumentPtr logLhs = lhsLogChild->getChildren().front();
          ArgumentPtr logRhs = mulExpr(lhsLogChild->getChildren().back(), rhsLogChild->getChildren().back());
          return logExpr(std::move(logLhs), std::move(logRhs));
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
  const std::vector<size_t> logChildrenIndices = findLogarithms(mulExprChildren);

  for (const size_t i : logChildrenIndices) {
    auto logChild = cast<IExpression>(mulExprChildren[i]);

    if (*logChild->getChildren().front() == *logExprChild->getChildren().front()) {
      logChild = mulToLogarithm(mulExprChildren, i);

      ArgumentPtr logLhs = logExprChild->getChildren().front();
      ArgumentPtr logRhs = mulExpr(logExprChild->getChildren().back(), logChild->getChildren().back());
      return logExpr(std::move(logLhs), std::move(logRhs));
    }
  }

  return {};
}

std::vector<size_t> AddExpr::findLogarithms(const ArgumentPtrVector &children) {
  std::vector<size_t> indices;

  for (const auto i : stdv::iota(0U, children.size())) {
    if (const auto childExpr = cast<const IExpression>(children[i]);
        childExpr && is<Log>(childExpr->getFunction())) {

      indices.emplace_back(i);
    }
  }

  return indices;
}

std::shared_ptr<const IExpression> AddExpr::mulToLogarithm(const ArgumentPtrVector &children, const size_t i) {
  ArgumentPtrVector mulChildren = children;
  const auto logExprChild = cast<const IExpression>(mulChildren[i]);

  mulChildren.erase(mulChildren.begin() + static_cast<ptrdiff_t>(i));

  const ArgumentPtr powRate = mulChildren.size() > 1 ? mulExpr(std::move(mulChildren)) : mulChildren.front();
  const ArgumentPtr logRhsChild = powExpr(logExprChild->getChildren().back(), powRate);

  return cast<IExpression>(logExpr(logExprChild->getChildren().front(), logRhsChild));
}

ArgumentPtr AddExpr::mulSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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

ArgumentPtr AddExpr::divSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  auto rhsExpr = cast<IExpression>(rhs);

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
      res = divExpr(std::move(numerator), std::move(denominator));
    }
    else {
      const ArgumentPtr &lhsNumerator = lhsExpr->getChildren().front();
      const ArgumentPtr &rhsNumerator = rhsExpr->getChildren().front();
      const ArgumentPtr &lhsDenominator = lhsExpr->getChildren().back();
      const ArgumentPtr &rhsDenominator = rhsExpr->getChildren().back();

      ArgumentPtr lhsNumeratorMulRhsDenominator = mulExpr(lhsNumerator, rhsDenominator);
      ArgumentPtr rhsNumeratorMulLhsDenominator = mulExpr(rhsNumerator, lhsDenominator);

      ArgumentPtr numerator = addExpr(std::move(lhsNumeratorMulRhsDenominator), std::move(rhsNumeratorMulLhsDenominator));
      ArgumentPtr denominator = mulExpr(lhsDenominator, rhsDenominator);
      res = divExpr(std::move(numerator), std::move(denominator));
    }
  }
  else if (rhsExpr && is<Div>(rhsExpr->getFunction())) {
    const ArgumentPtr &rhsNumerator = rhsExpr->getChildren().front();
    const ArgumentPtr &rhsDenominator = rhsExpr->getChildren().back();

    ArgumentPtr lhsMulRhsDenominator = mulExpr(lhs, rhsDenominator);

    ArgumentPtr numerator = addExpr(std::move(lhsMulRhsDenominator), rhsNumerator);
    ArgumentPtr denominator = rhsDenominator;
    res = divExpr(std::move(numerator), std::move(denominator));
  }

  return res;
}

ArgumentPtr AddExpr::trigSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  auto [lhsMulRate, lhsMulValue] = splitMulExpr(lhs, false);
  auto [rhsMulRate, rhsMulValue] = splitMulExpr(rhs, false);

  auto [lhsPowBase, lhsPowRate] = splitPowExpr(lhsMulValue);
  auto [rhsPowBase, rhsPowRate] = splitPowExpr(rhsMulValue);

  const auto lhsPowBaseExpr = cast<IExpression>(lhsPowBase);
  const auto rhsPowBaseExpr = cast<IExpression>(rhsPowBase);

  if (!lhsPowBaseExpr || *lhsPowRate != Integer(2)) {
    return {};
  }

  if (containsInfinity(lhsPowBase) || containsInfinity(rhsPowBase)) {
    return {};
  }

  const auto lhsPowBaseChild = lhsPowBaseExpr->getChildren().front();
  const auto lhsMulRateNum = cast<INumber>(lhsMulRate);

  if (rhsPowBaseExpr && *rhsPowRate == Integer(2)) {
    if (!is<Sin>(lhsPowBaseExpr->getFunction()) || !is<Cos>(rhsPowBaseExpr->getFunction())) {
      return {};
    }

    const auto rhsPowBaseChild = rhsPowBaseExpr->getChildren().front();

    if (*lhsPowBaseChild != *rhsPowBaseChild) {
      return {};
    }

    if (*lhsMulRate == *rhsMulRate) {
      return lhsMulRate;
    }

    auto rhsMulRateNum = cast<INumber>(rhsMulRate);

    if (lhsMulRateNum && rhsMulRateNum && *(*lhsMulRateNum + *rhsMulRateNum) == Integer(0)) {
      static const ArgumentPtr two = Integer(2).clone();

      ArgumentPtr res = cosExpr(
          mulExpr(lhsPowBaseExpr->getChildren().front(), two));

      return mulExpr(std::move(rhsMulRateNum), std::move(res));
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
