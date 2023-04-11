#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

const And AND;

AndExpression::AndExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(AND, children) {
}

ArgumentPtr AndExpression::logicNegate() const {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(makeRawFunctionExpression(Not(), {child}));
  }

  return makeFunctionExpression(Or(), negChildren);
}

ArgumentPtr AndExpression::preSimplify(size_t lhsChildNum, size_t rhsChildNum) const {
  const ArgumentPtr &lhsChild = children[lhsChildNum];
  const ArgumentPtr &rhsChild = children[rhsChildNum];

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? rhsChild : lhsChild;
  }
  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? lhsChild : rhsChild;
  }

  if (lhsChild->toString() == rhsChild->toString()) {
    return lhsChild;
  }

  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Not>(lhsExpr->getFunction()) &&
      lhsExpr->getChildren().front()->toString() == rhsChild->toString()) {
    return make_shared<Boolean>(false);
  }
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Not>(rhsExpr->getFunction()) &&
      rhsExpr->getChildren().front()->toString() == lhsChild->toString()) {
    return make_shared<Boolean>(false);
  }

  return {};
}

ArgumentPtr AndExpression::postSimplify(size_t lhsChildNum, size_t rhsChildNum) const {
  return preSimplify(lhsChildNum, rhsChildNum);
}

bool AndExpression::comparator(const ArgumentPtr &left, const ArgumentPtr &right) const {
  ArgumentPtr lhs;
  ArgumentPtr rhs;

  if (auto lhsExpr = cast<IExpression>(left); lhsExpr && is<Not>(lhsExpr->getFunction())) {
    lhs = lhsExpr->getChildren().front();
  }
  else {
    lhs = left;
  }

  if (auto rhsExpr = cast<IExpression>(right); rhsExpr && is<Not>(rhsExpr->getFunction())) {
    rhs = rhsExpr->getChildren().front();
  }
  else {
    rhs = right;
  }

  return IPolynomExpression::comparator(lhs, rhs);
}

}
