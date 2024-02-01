#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

AndExpression::AndExpression(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(And{}, std::move(inChildren)) {
}

AndExpression::SimplifyFunctionVector AndExpression::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AndExpression::boolSimplify,
      &AndExpression::equalSimplify,
      &AndExpression::notSimplify,
  };
  return simplifyFunctions;
}

AndExpression::SimplifyFunctionVector AndExpression::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AndExpression::orSimplify,
      &AndExpression::boolSimplify,
      &AndExpression::equalSimplify,
      &AndExpression::notSimplify,
  };
  return simplifyFunctions;
}

bool AndExpression::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr AndExpression::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto lhsBool = cast<Boolean>(lhs)) {
    return *lhsBool ? rhs : lhs;
  }

  if (const auto rhsBool = cast<Boolean>(rhs)) {
    return *rhsBool ? lhs : rhs;
  }

  return {};
}

ArgumentPtr AndExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return lhs;
  }

  return {};
}

ArgumentPtr AndExpression::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto rhsExpr = cast<IExpression>(rhs);
      rhsExpr &&
      is<Not>(rhsExpr->getFunction()) &&
      *rhsExpr->getChildren().front() == *lhs) {

    return Boolean(false).clone();
  }

  return {};
}

ArgumentPtr AndExpression::orSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  const auto lhsExpr = cast<IExpression>(lhs);
  const auto rhsExpr = cast<IExpression>(rhs);

  ArgumentPtrVector lhsChildren;
  ArgumentPtrVector rhsChildren;

  if (lhsExpr && is<Or>(lhsExpr->getFunction())) {
    lhsChildren = lhsExpr->getChildren();
  }
  else {
    lhsChildren.emplace_back(lhs);
  }

  if (rhsExpr && is<Or>(rhsExpr->getFunction())) {
    rhsChildren = rhsExpr->getChildren();
  }
  else {
    rhsChildren.emplace_back(rhs);
  }

  if (lhsChildren.size() == 1 && rhsChildren.size() == 1) {
    return {};
  }

  ArgumentPtrVector resultVect;

  for (const auto &lhsSubChild : lhsChildren) {
    for (const auto &rhsSubChild : rhsChildren) {
      resultVect.emplace_back(andExpr(lhsSubChild, rhsSubChild));
    }
  }

  ArgumentPtr res = orExpr(std::move(resultVect));
  return res;
}

}
