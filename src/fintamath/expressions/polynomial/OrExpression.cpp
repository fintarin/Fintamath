#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

OrExpression::OrExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(Or(), inChildren) {
}

std::string OrExpression::operatorChildToString(const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = inChild->toString();

  if (const auto &childExpr = cast<IExpression>(inChild); childExpr && is<And>(childExpr->getFunction())) {
    result = putInBrackets(result);
  }

  return prevChild ? (putInSpaces(func->toString()) + result) : result;
}

ArgumentPtr OrExpression::postSimplify() const {
  auto simplObj = IPolynomExpression::postSimplify();
  auto simpl = cast<OrExpression>(simplObj);

  if (!simpl) {
    return simplObj;
  }

  auto simplChildren = simpl->children;
  auto simplChildrenSizeInitial = simplChildren.size();

  for (size_t i = 0; i + 1 < simplChildren.size(); i++) {
    for (size_t j = i + 1; j < simplChildren.size(); j++) {
      if (auto res = simplifyAbsorption(simplChildren[i], simplChildren[j])) {
        simplChildren[i] = res;
        simplChildren.erase(simplChildren.begin() + ArgumentsPtrVector::difference_type(j));
        break;
      }
    }
  }

  if (simplChildren.size() != simplChildrenSizeInitial) {
    if (simplChildren.size() > 1) {
      ArgumentPtr res = makeExpr(Or(), simplChildren);
      postSimplifyChild(res);
      return res;
    }

    return simplChildren.front();
  }

  return simpl;
}

OrExpression::SimplifyFunctionsVector OrExpression::getFunctionsForSimplify() const {
  static const OrExpression::SimplifyFunctionsVector simplifyFunctions = {
      &OrExpression::simplifyNot,      //
      &OrExpression::simplifyBooleans, //
      &OrExpression::simplifyEqual,    //
  };
  return simplifyFunctions;
}

OrExpression::SimplifyFunctionsVector OrExpression::getFunctionsForPostSimplify() const {
  static const OrExpression::SimplifyFunctionsVector simplifyFunctions = {
      &OrExpression::simplifyAnd, //
  };
  return simplifyFunctions;
}

bool OrExpression::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr OrExpression::simplifyBooleans(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                           const ArgumentPtr &rhsChild) {
  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? lhsChild : rhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? rhsChild : lhsChild;
  }

  return {};
}

ArgumentPtr OrExpression::simplifyEqual(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                        const ArgumentPtr &rhsChild) {
  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr OrExpression::simplifyNot(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                      const ArgumentPtr &rhsChild) {
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Not>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return std::make_shared<Boolean>(true);
  }

  return {};
}

ArgumentPtr OrExpression::simplifyAnd(const IFunction & /*func*/, const ArgumentPtr &lhsChild,
                                      const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr || !is<And>(lhsExpr->getFunction()) || !is<And>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  if (rhsChildren.size() != lhsChildren.size()) {
    return {};
  }

  size_t resolutionIndex = lhsChildren.size();

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
      if (resolutionIndex != lhsChildren.size()) {
        return {};
      }

      resolutionIndex = i;
    }
  }

  if (resolutionIndex == lhsChildren.size()) {
    return {};
  }

  ArgumentsPtrVector resultChildren = lhsChildren;
  resultChildren.erase(resultChildren.begin() + ArgumentsPtrVector::difference_type(resolutionIndex));

  if (resultChildren.size() > 1) {
    ArgumentPtr res = makeExpr(And(), resultChildren);
    return res;
  }

  return resultChildren.front();
}

ArgumentPtr OrExpression::simplifyAbsorption(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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

  if (lhsChildren.size() == rhsChildren.size()) {
    return {};
  }

  ArgumentsPtrVector maxChildren = lhsChildren.size() > rhsChildren.size() ? lhsChildren : rhsChildren;
  ArgumentsPtrVector minChildren = lhsChildren.size() < rhsChildren.size() ? lhsChildren : rhsChildren;
  size_t matchCount = 0;

  for (size_t i = 0, j = 0; i < maxChildren.size() && j < minChildren.size(); i++) {
    if (*maxChildren[i] == *minChildren[j]) {
      matchCount++;
      j++;
    }
  }

  if (matchCount == minChildren.size()) {
    if (minChildren.size() > 1) {
      ArgumentPtr res = makeExpr(And(), minChildren);
      return res;
    }

    return minChildren.front();
  }

  return {};
}

}
