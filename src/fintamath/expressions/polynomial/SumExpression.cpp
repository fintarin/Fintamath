#include "fintamath/expressions/polynomial/SumExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

SumExpression::SumExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(Add(), inChildren) {
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
  static const SumExpression::SimplifyFunctionsVector simplifyFunctions = {
      &SumExpression::simplifyNumbers,       //
      &SumExpression::simplifyNegations,     //
      &SumExpression::sumRates,              //
      &SumExpression::simplifyLogarithms,    //
      &SumExpression::simplifyMulLogarithms, //
  };
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

ArgumentPtr SumExpression::simplifyLogarithms(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr || !is<Log>(lhsExpr->getFunction()) || !is<Log>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  if (*lhsChildren.front() == *rhsChildren.front()) {
    return makeFunctionExpression(
        Log(), {lhsChildren.front(), makeRawFunctionExpression(Mul(), {lhsChildren.back(), rhsChildren.back()})});
  }

  return {};
}

ArgumentPtr SumExpression::simplifyMulLogarithms(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  auto lhsExpr = cast<IExpression>(lhsChild);
  auto rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr) {
    return {};
  }

  if (is<Mul>(lhsExpr->getFunction()) && is<Mul>(rhsExpr->getFunction())) {
    ArgumentsPtrVector lhsExprChildren = lhsExpr->getChildren();
    ArgumentsPtrVector rhsExprChildren = rhsExpr->getChildren();

    std::vector<size_t> lhsLogarithmsIndexes = findLogarithms(lhsExprChildren);
    std::vector<size_t> rhsLogarithmsIndexes = findLogarithms(rhsExprChildren);

    for (size_t i : lhsLogarithmsIndexes) {
      auto lhsLogExpr = cast<IExpression>(lhsExprChildren[i]);

      for (size_t j : rhsLogarithmsIndexes) {
        auto rhsLogExpr = cast<IExpression>(rhsExprChildren[j]);

        if (*lhsLogExpr->getChildren().front() == *rhsLogExpr->getChildren().front()) {
          lhsLogExpr = mulToLogarithm(lhsExprChildren, i);
          rhsLogExpr = mulToLogarithm(rhsExprChildren, j);
          return makeFunctionExpression(Log(), {lhsLogExpr->getChildren().front(),
                                                makeRawFunctionExpression(Mul(), {lhsLogExpr->getChildren().back(),
                                                                                  rhsLogExpr->getChildren().back()})});
        }
      }
    }
  }

  std::shared_ptr<const IExpression> mulExpr;
  std::shared_ptr<const IExpression> logExpr;

  if (is<Mul>(lhsExpr->getFunction()) && is<Log>(rhsExpr->getFunction())) {
    mulExpr = lhsExpr;
    logExpr = rhsExpr;
  }
  else if (is<Mul>(rhsExpr->getFunction()) && is<Log>(lhsExpr->getFunction())) {
    mulExpr = rhsExpr;
    logExpr = lhsExpr;
  }
  else {
    return {};
  }

  ArgumentsPtrVector mulExprChildren = mulExpr->getChildren();
  std::vector<size_t> logarithmsIndexes = findLogarithms(mulExprChildren);

  for (size_t i : logarithmsIndexes) {
    auto childLogExpr = cast<IExpression>(mulExprChildren[i]);

    if (*childLogExpr->getChildren().front() == *logExpr->getChildren().front()) {
      childLogExpr = mulToLogarithm(mulExprChildren, i);
      return makeFunctionExpression(Log(), {logExpr->getChildren().front(),
                                            makeRawFunctionExpression(Mul(), {logExpr->getChildren().back(),
                                                                              childLogExpr->getChildren().back()})});
    }
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

std::vector<size_t> SumExpression::findLogarithms(const ArgumentsPtrVector &children) {
  std::vector<size_t> indexes;

  for (size_t i = 0; i < children.size(); i++) {
    if (const auto childExpr = cast<const IExpression>(children[i]); childExpr && is<Log>(childExpr->getFunction())) {

      indexes.emplace_back(i);
    }
  }

  return indexes;
}

std::shared_ptr<const IExpression> SumExpression::mulToLogarithm(const ArgumentsPtrVector &children, size_t i) {
  ArgumentsPtrVector mulChildren = children;
  auto logExpr = cast<const IExpression>(mulChildren[i]);

  mulChildren.erase(mulChildren.begin() + ArgumentsPtrVector::difference_type(i));

  const ArgumentPtr powRate =
      mulChildren.size() > 1 ? makeRawFunctionExpression(Mul(), mulChildren) : mulChildren.front();

  const ArgumentPtr powExpr = makeRawFunctionExpression(Pow(), {logExpr->getChildren().back(), powRate});

  return makeRawFunctionExpression(Log(), {logExpr->getChildren().front(), powExpr});
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
