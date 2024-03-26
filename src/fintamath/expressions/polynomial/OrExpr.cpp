#include "fintamath/expressions/polynomial/OrExpr.hpp"

#include <cstddef>
#include <ranges>
#include <string>
#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

using namespace detail;

OrExpr::OrExpr(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(Or{}, std::move(inChildren)) {
}

std::string OrExpr::childToString(const IOperator &oper, const ArgumentPtr &inChild, const ArgumentPtr &prevChild) const {
  std::string result = operatorChildToString(oper, inChild);

  if (const auto &childExpr = cast<IExpression>(inChild);
      childExpr && is<And>(childExpr->getFunction())) {

    result = putInBrackets(result);
  }

  return prevChild ? (putInSpaces(func->toString()) + result) : result;
}

ArgumentPtr OrExpr::postSimplify() const {
  ArgumentPtr simplObj = IPolynomExpression::postSimplify();
  auto simpl = cast<OrExpr>(simplObj);

  if (!simpl) {
    return simplObj;
  }

  ArgumentPtrVector simplChildren = simpl->children;
  const size_t simplChildrenSizeInitial = simplChildren.size();

  // TODO: use more efficient algorithm
  for (size_t i = 0; i + 1 < simplChildren.size(); i++) {
    for (size_t j = i + 1; j < simplChildren.size(); j++) {
      if (auto res = absorptionSimplify(simplChildren[i], simplChildren[j])) {
        simplChildren[i] = std::move(res);
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

OrExpr::SimplifyFunctionVector OrExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &OrExpr::notSimplify,
      &OrExpr::boolSimplify,
      &OrExpr::equalSimplify,
  };
  return simplifyFunctions;
}

OrExpr::SimplifyFunctionVector OrExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &OrExpr::andSimplify,
      &OrExpr::notSimplify,
      &OrExpr::boolSimplify,
      &OrExpr::equalSimplify,
  };
  return simplifyFunctions;
}

bool OrExpr::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr OrExpr::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {

  if (const auto lhsBool = cast<Boolean>(lhs)) {
    return *lhsBool ? lhs : rhs;
  }

  if (const auto rhsBool = cast<Boolean>(rhs)) {
    return *rhsBool ? rhs : lhs;
  }

  return {};
}

ArgumentPtr OrExpr::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return lhs;
  }

  return {};
}

ArgumentPtr OrExpr::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto rhsExpr = cast<IExpression>(rhs);
      rhsExpr &&
      is<Not>(rhsExpr->getFunction()) &&
      *rhsExpr->getChildren().front() == *lhs) {

    return Boolean(true).clone();
  }

  return {};
}

ArgumentPtr OrExpr::andSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

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

    if (const auto lhsSubChildNotExpr = cast<IExpression>(lhsSubChild);
        lhsSubChildNotExpr &&
        is<Not>(lhsSubChildNotExpr->getFunction())) {

      isLhsSubChildNot = true;
      lhsSubChild = lhsSubChildNotExpr->getChildren().front();
    }

    bool isRhsSubChildNot = false;

    if (const auto rhsSubChildNotExpr = cast<IExpression>(rhsSubChild);
        rhsSubChildNotExpr &&
        is<Not>(rhsSubChildNotExpr->getFunction())) {

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

ArgumentPtr OrExpr::absorptionSimplify(const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

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

  const ArgumentPtrVector maxChildren = lhsChildren.size() > rhsChildren.size() ? lhsChildren : rhsChildren;
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
