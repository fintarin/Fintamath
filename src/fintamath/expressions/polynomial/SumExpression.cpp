#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Add ADD;

const SumExpression::SimplifyFunctionsVector SumExpression::simplifyFunctions = {
    &SumExpression::simplifyNumbers,   //
    &SumExpression::simplifyNegations, //
    &SumExpression::sumRates,          //
};

SumExpression::SumExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(ADD, inChildren) {
}

std::string SumExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  ArgumentPtr child = inChild;
  bool isChildNegated = false;

  if (auto negExpr = cast<IExpression>(inChild); negExpr && is<Neg>(negExpr->getFunction())) {
    child = negExpr->getChildren().front();
    isChildNegated = true;
  }

  std::string result = child->toString();

  if (!isChildNegated && result.size() > 1 && result.front() == Neg().toString().front()) {
    isChildNegated = true;
    result = result.substr(1, result.size() - 1);
  }

  std::string funcStr;

  if (isChildNegated) {
    funcStr = Sub().toString();
  }
  else if (prevChild) {
    funcStr = Add().toString();
  }

  if (!funcStr.empty()) {
    if (prevChild) {
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

SumExpression::SimplifyFunctionsVector SumExpression::getFunctionsForSimplify() const {
  return simplifyFunctions;
}

ArgumentPtr SumExpression::simplifyNumbers(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == ZERO) {
    return rhsChild;
  }
  if (*rhsChild == ZERO) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr SumExpression::simplifyNegations(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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

ArgumentPtr SumExpression::addRatesToValue(const ArgumentsPtrVector &rates, const ArgumentPtr &value) {
  ArgumentPtr ratesSum = makeRawFunctionExpression(Add(), rates);
  return makeFunctionExpression(Mul(), ArgumentsPtrVector{ratesSum, value});
}

ArgumentPtr SumExpression::sumRates(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto [lhsChildRate, lhsChildValue] = getRateValuePair(lhsChild);
  auto [rhsChildRate, rhsChildValue] = getRateValuePair(rhsChild);

  if (*lhsChildValue == *rhsChildValue) {
    return addRatesToValue({lhsChildRate, rhsChildRate}, lhsChildValue);
  }

  return {};
}

}
