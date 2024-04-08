#include "fintamath/expressions/polynomial/AndExpr.hpp"

#include <utility>

#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IPolynomExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/AndOper.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(AndExpr)

AndExpr::AndExpr(ArgumentPtrVector inChildren)
    : IPolynomExpressionCRTP(And{}, std::move(inChildren)) {
}

const std::shared_ptr<IFunction> &AndExpr::getOutputFunction() const {
  static const std::shared_ptr<IFunction> oper = std::make_shared<AndOper>();
  return oper;
}

AndExpr::SimplifyFunctionVector AndExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AndExpr::boolSimplify,
      &AndExpr::equalSimplify,
      &AndExpr::notSimplify,
  };
  return simplifyFunctions;
}

AndExpr::SimplifyFunctionVector AndExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &AndExpr::orSimplify,
      &AndExpr::boolSimplify,
      &AndExpr::equalSimplify,
      &AndExpr::notSimplify,
  };
  return simplifyFunctions;
}

bool AndExpr::isComparableOrderInversed() const {
  return true;
}

ArgumentPtr AndExpr::boolSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto lhsBool = cast<Boolean>(lhs)) {
    return *lhsBool ? rhs : lhs;
  }

  if (const auto rhsBool = cast<Boolean>(rhs)) {
    return *rhsBool ? lhs : rhs;
  }

  return {};
}

ArgumentPtr AndExpr::equalSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (*lhs == *rhs) {
    return lhs;
  }

  return {};
}

ArgumentPtr AndExpr::notSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
  if (const auto lhsExpr = cast<IExpression>(lhs);
      lhsExpr &&
      is<Not>(lhsExpr->getFunction()) &&
      *lhsExpr->getChildren().front() == *rhs) {

    return Boolean(false).clone();
  }

  return {};
}

ArgumentPtr AndExpr::orSimplify(const IFunction & /*func*/, const ArgumentPtr &lhs, const ArgumentPtr &rhs) {
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
