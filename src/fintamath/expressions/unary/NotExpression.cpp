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

NotExpression::NotExpression(const ArgumentPtr &inChild) : IUnaryExpressionCRTP(Not(), inChild) {
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::simplifyNestedNot, //
  };
  return simplifyFunctions;
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForPreSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::callNotFunction, //
  };
  return simplifyFunctions;
}

NotExpression::SimplifyFunctionsVector NotExpression::getFunctionsForPostSimplify() const {
  static const NotExpression::SimplifyFunctionsVector simplifyFunctions = {
      &NotExpression::simplifyLogicNegatable, //
  };
  return simplifyFunctions;
}

ArgumentPtr NotExpression::callNotFunction(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (ArgumentPtr res = callFunction(Not(), {rhs})) {
    return res;
  }

  return {};
}

ArgumentPtr NotExpression::simplifyLogicNegatable(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!rhsExpr) {
    return {};
  }

  if (const auto op = cast<IOperator>(rhsExpr->getFunction());
      op && op->getOperatorPriority() == IOperator::Priority::Comparison) {
    return makeExpr(*cast<IFunction>(getLogicOppositeFunction(*op)), rhsExpr->getChildren());
  }

  if (is<Or>(rhsExpr->getFunction())) {
    ArgumentsPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = makeExpr(Not(), child);
    }

    return makeExpr(And(), children)->toMinimalObject();
  }

  if (is<And>(rhsExpr->getFunction())) {
    ArgumentsPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = makeExpr(Not(), child);
    }

    return makeExpr(Or(), children)->toMinimalObject();
  }

  return {};
}

ArgumentPtr NotExpression::simplifyNestedNot(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (const auto expr = cast<NotExpression>(rhs)) {
    return expr->child;
  }

  return {};
}

std::shared_ptr<IFunction> NotExpression::getLogicOppositeFunction(const IFunction &function) {
  static const std::map<std::string, std::shared_ptr<IFunction>, std::less<>> oppositeFunctions = {
      {Eqv().toString(), std::make_shared<Neqv>()},     //
      {Neqv().toString(), std::make_shared<Eqv>()},     //
      {More().toString(), std::make_shared<LessEqv>()}, //
      {Less().toString(), std::make_shared<MoreEqv>()}, //
      {MoreEqv().toString(), std::make_shared<Less>()}, //
      {LessEqv().toString(), std::make_shared<More>()}, //
  };
  return oppositeFunctions.at(function.toString());
}

}
