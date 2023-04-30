#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

const Or OR;

OrExpression::OrExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(OR, inChildren) {
}

ArgumentPtr OrExpression::logicNegate() const {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(makeRawFunctionExpression(Not(), {child}));
  }

  return makeFunctionExpression(And(), negChildren);
}

std::string OrExpression::childToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = inChild->toString();

  if (const auto &childExpr = cast<IExpression>(inChild); childExpr && is<And>(childExpr->getFunction())) {
    result = putInBrackets(result);
  }

  return prevChild ? (putInSpaces(func->toString()) + result) : result;
}

ArgumentPtr OrExpression::postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const {
  const ArgumentPtr &lhsChild = children[lhsChildNum];
  const ArgumentPtr &rhsChild = children[rhsChildNum];

  if (auto res = simplifyBooleans(lhsChild, rhsChild)) {
    return res;
  }

  if (auto res = simplifyAnd(lhsChild, rhsChild)) {
    return res;
  }

  return {};
}

// TODO: improve logic minimization
OrExpression::SimplifyFunctionsVector OrExpression::getFunctionsForSimplify() const {
  return {
      &OrExpression::simplifyEqual, //
      &OrExpression::simplifyNot,   //
  };
}

bool OrExpression::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr OrExpression::simplifyEqual(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr OrExpression::simplifyNot(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Not>(lhsExpr->getFunction()) && *lhsExpr->getChildren().front() == *rhsChild) {
    return std::make_shared<Boolean>(true);
  }

  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Not>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return std::make_shared<Boolean>(true);
  }

  return {};
}

ArgumentPtr OrExpression::simplifyAnd(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  ArgumentPtr lhs = lhsChild;
  ArgumentPtr rhs = rhsChild;

  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<And>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhs);
  }

  if (rhsExpr && is<And>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhs);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  if (auto res = simplifyAbsorption(lhsChildren, rhsChildren)) {
    return res;
  }

  return simplifyResolution(lhsChildren, rhsChildren);
}

ArgumentPtr OrExpression::simplifyAbsorption(const ArgumentsPtrVector &lhsChildren,
                                             const ArgumentsPtrVector &rhsChildren) {
  if (lhsChildren.size() == rhsChildren.size()) {
    return {};
  }

  ArgumentsPtrVector maxChildren = lhsChildren.size() > rhsChildren.size() ? lhsChildren : rhsChildren;
  ArgumentsPtrVector minChildren = lhsChildren.size() < rhsChildren.size() ? lhsChildren : rhsChildren;
  bool absorptionFound = false;

  for (size_t i = 0; i < maxChildren.size(); i += minChildren.size()) {
    size_t j = 0;

    for (; j < minChildren.size(); j++) {
      if (*maxChildren[i + j] != *minChildren[j]) {
        break;
      }
    }

    if (j == minChildren.size()) {
      absorptionFound = true;
      break;
    }
  }

  if (absorptionFound) {
    return minChildren.size() > 1 ? makeFunctionExpression(And(), minChildren) : minChildren.front();
  }

  return {};
}

ArgumentPtr OrExpression::simplifyResolution(const ArgumentsPtrVector &lhsChildren,
                                             const ArgumentsPtrVector &rhsChildren) {
  if (lhsChildren.size() != rhsChildren.size()) {
    return {};
  }

  int64_t resolutionIndex = -1;

  for (size_t i = 0; i < lhsChildren.size(); i++) {
    ArgumentPtr lhsSubChild = lhsChildren[i];
    ArgumentPtr rhsSubChild = rhsChildren[i];

    bool isLhsSubChildNot = false;

    if (auto lhsSubChildNotExpr = cast<IExpression>(lhsSubChild);
        lhsSubChildNotExpr && is<Not>(lhsSubChildNotExpr->getFunction())) {

      isLhsSubChildNot = true;
      lhsSubChild = lhsSubChildNotExpr->getChildren().front();
    }

    bool isRhsSubChildNot = false;

    if (auto rhsSubChildNotExpr = cast<IExpression>(rhsSubChild);
        rhsSubChildNotExpr && is<Not>(rhsSubChildNotExpr->getFunction())) {

      isRhsSubChildNot = true;
      rhsSubChild = rhsSubChildNotExpr->getChildren().front();
    }

    if (*lhsSubChild != *rhsSubChild) {
      return {};
    }

    if (isLhsSubChildNot != isRhsSubChildNot) {
      if (resolutionIndex != -1) {
        return {};
      }

      resolutionIndex = int64_t(i);
    }
  }

  if (resolutionIndex == -1) {
    return {};
  }

  ArgumentsPtrVector resultChildren = lhsChildren;
  resultChildren.erase(resultChildren.begin() + resolutionIndex);

  return resultChildren.size() > 1 ? makeFunctionExpression(And(), resultChildren) : resultChildren.front();
}

ArgumentPtr OrExpression::simplifyBooleans(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? lhsChild : rhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? rhsChild : lhsChild;
  }

  return {};
}
}
