#include "fintamath/expressions/polynomial/OrExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

const Or OR;

OrExpression::OrExpression(const ArgumentsPtrVector &children) : IPolynomExpressionCRTP(OR, children) {
}

ArgumentPtr OrExpression::logicNegate() const {
  ArgumentsPtrVector negChildren;

  for (const auto &child : children) {
    negChildren.emplace_back(makeRawFunctionExpression(Not(), {child}));
  }

  return makeFunctionExpression(And(), negChildren);
}

ArgumentPtr OrExpression::postSimplify(size_t lhsChildNum, size_t rhsChildNum) const {
  const ArgumentPtr &lhsChild = children[lhsChildNum];
  const ArgumentPtr &rhsChild = children[rhsChildNum];

  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? lhsChild : rhsChild;
  }
  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? rhsChild : lhsChild;
  }

  if (lhsChild->toString() == rhsChild->toString()) {
    return lhsChild;
  }

  if (const auto lhsExpr = cast<IExpression>(lhsChild);
      lhsExpr && is<Not>(lhsExpr->getFunction()) && lhsExpr->getChildren().front()->toString() == rhsChild->toString()) {
    return make_shared<Boolean>(true);
  }
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr && is<Not>(rhsExpr->getFunction()) && rhsExpr->getChildren().front()->toString() == lhsChild->toString()) {
    return make_shared<Boolean>(true);
  }

  return {};
}

}
