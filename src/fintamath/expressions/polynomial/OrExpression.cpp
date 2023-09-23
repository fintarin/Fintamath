#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

OrExpression::OrExpression(const ArgumentPtrVector &inChildren)
    : IPolynomExpressionCRTP(Or(), inChildren) {
}

std::string OrExpression::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = operatorChildToString(oper, inChild);

  if (const auto &childExpr = cast<IExpression>(inChild);
      childExpr && is<And>(childExpr->getFunction())) {

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

  // TODO: use more efficient algorithm
  for (size_t i = 0; i + 1 < simplChildren.size(); i++) {
    for (size_t j = i + 1; j < simplChildren.size(); j++) {
      if (auto res = absorptionSimplify(simplChildren[i], simplChildren[j])) {
        simplChildren[i] = res;
        simplChildren.erase(simplChildren.begin() + ptrdiff_t(j));
        j--;
      }
    }
  }

  if (simplChildren.size() != simplChildrenSizeInitial) {
    if (simplChildren.size() > 1) {
      ArgumentPtr res = orExpr(simplChildren);
      postSimplifyChild(res);
      return res;
    }

    return simplChildren.front();
  }

  return simpl;
}

OrExpression::SimplifyFunctionVector OrExpression::getFunctionsForPreSimplify() const {
  static const OrExpression::SimplifyFunctionVector simplifyFunctions = {
      &OrExpression::notSimplify,
      &OrExpression::boolSimplify,
      &OrExpression::equalSimplify,
  };
  return simplifyFunctions;
}

OrExpression::SimplifyFunctionVector OrExpression::getFunctionsForPostSimplify() const {
  static const OrExpression::SimplifyFunctionVector simplifyFunctions = {
      &OrExpression::andSimplify,
      &OrExpression::notSimplify,
      &OrExpression::boolSimplify,
      &OrExpression::equalSimplify,
  };
  return simplifyFunctions;
}

bool OrExpression::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr OrExpression::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? lhsChild : rhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? rhsChild : lhsChild;
  }

  return {};
}

ArgumentPtr OrExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr OrExpression::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr &&
      is<Not>(rhsExpr->getFunction()) &&
      *rhsExpr->getChildren().front() == *lhsChild) {

    return Boolean(true).clone();
  }

  return {};
}

ArgumentPtr OrExpression::andSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr ||
      !is<And>(lhsExpr->getFunction()) || !is<And>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentPtrVector rhsChildren = rhsExpr->getChildren();

  if (rhsChildren.size() != lhsChildren.size()) {
    return {};
  }

  size_t resolutionIndex = lhsChildren.size();

  for (auto i : std::views::iota(0U, lhsChildren.size())) {
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

  ArgumentPtrVector resultChildren = lhsChildren;
  resultChildren.erase(resultChildren.begin() + ptrdiff_t(resolutionIndex));

  if (resultChildren.size() > 1) {
    ArgumentPtr res = andExpr(resultChildren);
    return res;
  }

  return resultChildren.front();
}

ArgumentPtr OrExpression::absorptionSimplify(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  ArgumentPtr lhs = lhsChild;
  ArgumentPtr rhs = rhsChild;

  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  ArgumentPtrVector lhsChildren;
  ArgumentPtrVector rhsChildren;

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

  ArgumentPtrVector maxChildren = lhsChildren.size() > rhsChildren.size() ? lhsChildren : rhsChildren;
  ArgumentPtrVector minChildren = lhsChildren.size() < rhsChildren.size() ? lhsChildren : rhsChildren;
  size_t matchCount = 0;

  {
    size_t i = 0;
    size_t j = 0;

    while (i < maxChildren.size() && j < minChildren.size()) {
      if (*maxChildren[i] == *minChildren[j]) {
        matchCount++;
        j++;
      }

      i++;
    }
  }

  if (matchCount == minChildren.size()) {
    if (minChildren.size() > 1) {
      ArgumentPtr res = andExpr(minChildren);
      return res;
    }

    return minChildren.front();
  }

  return {};
}

}
