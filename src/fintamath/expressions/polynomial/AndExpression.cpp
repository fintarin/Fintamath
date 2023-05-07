#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

const And AND;

const AndExpression::SimplifyFunctionsVector AndExpression::simplifyFunctions = {
    &AndExpression::simplifyBooleans, //
    &AndExpression::simplifyEqual,    //
    &AndExpression::simplifyNot,      //
};

AndExpression::AndExpression(const ArgumentsPtrVector &inChildren) : IPolynomExpressionCRTP(AND, inChildren) {
}

ArgumentPtr AndExpression::logicNegate() const {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(makeRawFunctionExpression(Not(), {child}));
  }

  return makeFunctionExpression(Or(), negChildren);
}

AndExpression::SimplifyFunctionsVector AndExpression::getFunctionsForSimplify() const {
  return simplifyFunctions;
}

ArgumentPtr AndExpression::postSimplifyChildren(size_t lhsChildNum, size_t rhsChildNum) const {
  const ArgumentPtr &lhsChild = children[lhsChildNum];
  const ArgumentPtr &rhsChild = children[rhsChildNum];

  if (auto res = simplifyOr(lhsChild, rhsChild)) {
    return res;
  }

  return {};
}

bool AndExpression::isComparableOrderInversed() const {
  return true;
}

bool AndExpression::isUnaryOperatorsOrderInversed() const {
  return true;
}

ArgumentPtr AndExpression::simplifyEqual(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr AndExpression::simplifyNot(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Not>(rhsExpr->getFunction()) && *rhsExpr->getChildren().front() == *lhsChild) {
    return std::make_shared<Boolean>(false);
  }

  return {};
}

ArgumentPtr AndExpression::simplifyOr(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  std::shared_ptr<const IExpression> lhsExpr = cast<IExpression>(lhsChild);
  std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhsChild);

  ArgumentsPtrVector lhsChildren;
  ArgumentsPtrVector rhsChildren;

  if (lhsExpr && is<Or>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhsChild);
  }

  if (rhsExpr && is<Or>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhsChild);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentsPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(makeRawFunctionExpression(And(), ArgumentsPtrVector{lhsSubChild, rhsSubChild}));
    }
  }

  return makeFunctionExpression(Or(), resultVect);
}

ArgumentPtr AndExpression::simplifyBooleans(const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? rhsChild : lhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? lhsChild : rhsChild;
  }

  return {};
}

}
