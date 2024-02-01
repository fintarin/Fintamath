#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

OrExpression::OrExpression(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Or(), std::move(inChildren)) {
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
  ArgumentPtr simplObj = IPolynomExpression::postSimplify();
  auto simpl = cast<OrExpression>(simplObj);

  if (!simpl) {
    return simplObj;
  }

  ArgumentPtrVector simplChildren = simpl->children;
  size_t simplChildrenSizeInitial = simplChildren.size();

  // TODO: use more efficient algorithm
  for (size_t i = 0; i + 1 < simplChildren.size(); i++) {
    for (size_t j = i + 1; j < simplChildren.size(); j++) {
      if (auto res = absorptionSimplify(simplChildren[i], simplChildren[j])) {
        simplChildren[i] = res;
        simplChildren.erase(simplChildren.begin() + static_cast<ptrdiff_t>(j));
        j--;
      }
    }
  }

  if (simplChildren.size() != simplChildrenSizeInitial) {
    if (simplChildren.size() > 1) {
      ArgumentPtr res = orExpr(std::move(simplChildren));
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

ArgumentPtr OrExpression::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {

  if (const auto lhsBool = cast<Boolean>(lhs)) {
    return *lhsBool ? lhs : rhs;
  }

  if (const auto rhsBool = cast<Boolean>(rhs)) {
    return *rhsBool ? rhs : lhs;
  }

  return {};
}

ArgumentPtr OrExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return lhs;
  }

  return {};
}

ArgumentPtr OrExpression::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto rhsExpr = cast<IExpression>(rhs);
      rhsExpr &&
      is<Not>(rhsExpr->getFunction()) &&
      *rhsExpr->getChildren().front() == *lhs) {

    return Boolean(true).clone();
  }

  return {};
}

ArgumentPtr OrExpression::andSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhs);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!lhsExpr || !rhsExpr ||
      !is<And>(lhsExpr->getFunction()) || !is<And>(rhsExpr->getFunction())) {
    return {};
  }

  const ArgumentPtrVector &lhsChildren = lhsExpr->getChildren();
  const ArgumentPtrVector &rhsChildren = rhsExpr->getChildren();

  if (rhsChildren.size() != lhsChildren.size()) {
    return {};
  }

  size_t resolutionIndex = lhsChildren.size();

  for (const auto i : stdv::iota(0U, lhsChildren.size())) {
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
  resultChildren.erase(resultChildren.begin() + static_cast<ptrdiff_t>(resolutionIndex));

  if (resultChildren.size() > 1) {
    ArgumentPtr res = andExpr(std::move(resultChildren));
    return res;
  }

  return resultChildren.front();
}

ArgumentPtr OrExpression::absorptionSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
      ArgumentPtr res = andExpr(std::move(minChildren));
      return res;
    }

    return minChildren.front();
  }

  return {};
}

}
