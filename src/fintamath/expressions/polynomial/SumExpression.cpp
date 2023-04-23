#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Inv.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Add ADD;

SumExpression::SumExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(ADD, children) {
}

string SumExpression::childToString(const ArgumentPtr &inChild, bool isFirst) const {
  ArgumentPtr child = inChild;
  bool isChildNegated = false;

  if (auto negExpr = cast<IExpression>(inChild); negExpr && is<Neg>(negExpr->getFunction())) {
    child = negExpr->getChildren().front();
    isChildNegated = true;
  }

  string result;

  if (auto powExpr = cast<IExpression>(child); powExpr && is<Inv>(powExpr->getFunction())) {
    result = powExpr->getChildren().front()->toString();
  }
  else {
    result = child->toString();
  }

  if (!isChildNegated && result.size() > 1 && result.front() == Neg().toString().front()) {
    isChildNegated = true;
    result = result.substr(1, result.size() - 1);
  }

  string funcStr;

  if (isChildNegated) {
    funcStr = Sub().toString();
  }
  else if (!isFirst) {
    funcStr = Add().toString();
  }

  if (!funcStr.empty()) {
    if (!isFirst) {
      funcStr = putInSpaces(funcStr);
    }

    result = funcStr + result;
  }

  return result;
}

ArgumentPtr SumExpression::negate() const {
  SumExpression neg = *this;

  for (auto &child : neg.children) {
    child = makeRawFunctionExpression(Neg(), {child});
  }

  return neg.simplify();
}

SumExpression::FunctionsVector SumExpression::getSimplifyFunctions() const {
  return {
      &SumExpression::simplifyNumber,         //
      &SumExpression::simplifyNegation,       //
      &SumExpression::coefficientsProcessing, //
  };
}

ArgumentPtr SumExpression::simplifyNumber(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == ZERO) {
    return rhsChild;
  }
  if (*rhsChild == ZERO) {
    return lhsChild;
  }

  bool lhsNeg = false;
  bool rhsNeg = false;

  const shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  const shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  shared_ptr<const INumber> lhsNum = nullptr;
  shared_ptr<const INumber> rhsNum = nullptr;

  if (lhsExpr && is<Neg>(lhsExpr->getFunction())) {
    lhsNum = cast<INumber>(lhsExpr->getChildren().front());

    if (lhsNum) {
      lhsNum = -(*lhsNum);
    }
  }
  else {
    lhsNum = cast<INumber>(lhsChild);
  }

  if (rhsExpr && is<Neg>(rhsExpr->getFunction())) {
    rhsNum = cast<INumber>(rhsExpr->getChildren().front());

    if (rhsNum) {
      rhsNum = -(*rhsNum);
    }
  }
  else {
    rhsNum = cast<INumber>(rhsChild);
  }

  if (lhsNum && rhsNum) {
    return *lhsNum + *rhsNum;
  }

  return {};
}

ArgumentPtr SumExpression::simplifyNegation(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Neg>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return ZERO.clone();
  }

  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Neg>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return ZERO.clone();
  }

  return {};
}

std::pair<ArgumentPtr, ArgumentPtr> SumExpression::getRateValuePair(const ArgumentPtr &inChild) {
  ArgumentPtr rate;
  ArgumentPtr value;

  if (const auto mulExpr = cast<IExpression>(inChild); mulExpr && is<Mul>(mulExpr->getFunction())) {
    const ArgumentsPtrVector mulExprChildren = mulExpr->getChildren();

    if (is<INumber>(mulExprChildren.front())) {
      rate = mulExprChildren.front();

      if (mulExprChildren.size() == 2) {
        value = mulExprChildren[1];
      }
      else {
        value = makeFunctionExpression(Mul(), ArgumentsPtrVector{mulExprChildren.begin() + 1, mulExprChildren.end()});
      }
    }
  }
  else if (const auto negExpr = cast<IExpression>(inChild); negExpr && is<Neg>(negExpr->getFunction())) {
    rate = NEG_ONE.clone();
    value = negExpr->getChildren().front();
  }

  if (rate == nullptr || value == nullptr) {
    rate = ONE.clone();
    value = inChild;
  }

  return {rate, value};
}

ArgumentPtr SumExpression::addRateToValue(const ArgumentsPtrVector &rate, const ArgumentPtr &value) {
  ArgumentPtr rateSum = makeRawFunctionExpression(Add(), rate);
  return makeFunctionExpression(Mul(), ArgumentsPtrVector{rateSum, value});
}

ArgumentPtr SumExpression::coefficientsProcessing(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::pair<ArgumentPtr, ArgumentPtr> lhsRateValuePair = getRateValuePair(lhsChild);
  std::pair<ArgumentPtr, ArgumentPtr> rhsRateValuePair = getRateValuePair(rhsChild);

  ArgumentPtr lhsChildRate = lhsRateValuePair.first;
  ArgumentPtr rhsChildRate = rhsRateValuePair.first;

  ArgumentPtr lhsChildValue = lhsRateValuePair.second;
  ArgumentPtr rhsChildValue = rhsRateValuePair.second;

  if (lhsChildValue->toString() == rhsChildValue->toString()) {
    return addRateToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

}
