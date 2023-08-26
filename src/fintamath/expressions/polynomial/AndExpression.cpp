#include "fintamath/expressions/polynomial/AndExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

AndExpression::AndExpression(const ArgumentsPtrVector &inChildren)
    : IPolynomExpressionCRTP(And(), inChildren) {
}

AndExpression::SimplifyFunctionsVector AndExpression::getFunctionsForPreSimplify() const {
  static const AndExpression::SimplifyFunctionsVector simplifyFunctions = {
      &AndExpression::boolSimplify,
      &AndExpression::equalSimplify,
      &AndExpression::notSimplify,
  };
  return simplifyFunctions;
}

AndExpression::SimplifyFunctionsVector AndExpression::getFunctionsForPostSimplify() const {
  static const AndExpression::SimplifyFunctionsVector simplifyFunctions = {
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

ArgumentPtr AndExpression::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto lhsBool = cast<Boolean>(lhsChild)) {
    return *lhsBool ? rhsChild : lhsChild;
  }

  if (const auto rhsBool = cast<Boolean>(rhsChild)) {
    return *rhsBool ? lhsChild : rhsChild;
  }

  return {};
}

ArgumentPtr AndExpression::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (*lhsChild == *rhsChild) {
    return lhsChild;
  }

  return {};
}

ArgumentPtr AndExpression::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
  if (const auto rhsExpr = cast<IExpression>(rhsChild);
      rhsExpr &&
      is<Not>(rhsExpr->getFunction()) &&
      *rhsExpr->getChildren().front() == *lhsChild) {

    return std::make_shared<Boolean>(false);
  }

  return {};
}

ArgumentPtr AndExpression::orSimplify(const IFunction & /*func*/, const ArgumentPtr &lhsChild, const ArgumentPtr &rhsChild) {
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
      resultVect.emplace_back(andExpr(lhsSubChild, rhsSubChild));
    }
  }

  ArgumentPtr res = orExpr(resultVect);
  return res;
}

}
