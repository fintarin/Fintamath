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
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  if (!lhsExpr || !rhsExpr || !is<And>(lhsExpr->getFunction()) || !is<And>(rhsExpr->getFunction())) {
    return {};
  }

  ArgumentsPtrVector lhsChildren = lhsExpr->getChildren();
  ArgumentsPtrVector rhsChildren = rhsExpr->getChildren();

  if (lhsChildren.size() != rhsChildren.size()) {
    return {};
  }

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
      lhsChildren.erase(lhsChildren.begin() + int64_t(i));
      rhsChildren.erase(rhsChildren.begin() + int64_t(i));
      break;
    }
  }

  ArgumentPtr lhsRes = lhsChildren.size() > 1 ? makeRawFunctionExpression(And(), lhsChildren) : lhsChildren.front();
  ArgumentPtr rhsRes = rhsChildren.size() > 1 ? makeRawFunctionExpression(And(), rhsChildren) : rhsChildren.front();

  if (*lhsRes != *rhsRes) {
    return {};
  }

  return lhsRes;
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
