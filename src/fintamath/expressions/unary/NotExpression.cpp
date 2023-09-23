#include "fintamath/expressions/unary/NotExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/comparison/Eqv.hpp"
#include "fintamath/functions/comparison/Less.hpp"
#include "fintamath/functions/comparison/LessEqv.hpp"
#include "fintamath/functions/comparison/More.hpp"
#include "fintamath/functions/comparison/MoreEqv.hpp"
#include "fintamath/functions/comparison/Neqv.hpp"
#include "fintamath/functions/logic/And.hpp"
#include "fintamath/functions/logic/Not.hpp"
#include "fintamath/functions/logic/Or.hpp"

namespace fintamath {

NotExpression::NotExpression(const ArgumentPtr &inChild)
    : IUnaryExpressionCRTP(Not(), inChild) {
}

NotExpression::SimplifyFunctionVector NotExpression::getFunctionsForPreSimplify() const {
  static const NotExpression::SimplifyFunctionVector simplifyFunctions = {
      &NotExpression::callFunctionSimplify,
      &NotExpression::nestedNotSimplify,
  };
  return simplifyFunctions;
}

NotExpression::SimplifyFunctionVector NotExpression::getFunctionsForPostSimplify() const {
  static const NotExpression::SimplifyFunctionVector simplifyFunctions = {
      &NotExpression::logicNegatableSimplify,
      &NotExpression::nestedNotSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr NotExpression::callFunctionSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (ArgumentPtr res = callFunction(Not(), {rhs})) {
    return res;
  }

  return {};
}

ArgumentPtr NotExpression::logicNegatableSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!rhsExpr) {
    return {};
  }

  ArgumentPtr res;

  if (const auto op = cast<IOperator>(rhsExpr->getFunction());
      op && op->getOperatorPriority() == IOperator::Priority::Comparison) {

    res = makeExpr(*cast<IFunction>(getLogicOppositeFunction(*op)), rhsExpr->getChildren());
  }
  else if (is<Or>(rhsExpr->getFunction())) {
    ArgumentPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = notExpr(child);
    }

    res = andExpr(children);
  }
  else if (is<And>(rhsExpr->getFunction())) {
    ArgumentPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = notExpr(child);
    }

    res = orExpr(children);
  }

  return res;
}

ArgumentPtr NotExpression::nestedNotSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (const auto expr = cast<NotExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

std::shared_ptr<IFunction> NotExpression::getLogicOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Eqv().toString(), std::make_shared<Neqv>()},
      {Neqv().toString(), std::make_shared<Eqv>()},
      {More().toString(), std::make_shared<LessEqv>()},
      {Less().toString(), std::make_shared<MoreEqv>()},
      {MoreEqv().toString(), std::make_shared<Less>()},
      {LessEqv().toString(), std::make_shared<More>()},
  };
  return oppositeFunctions.at(function.toString());
}

}
