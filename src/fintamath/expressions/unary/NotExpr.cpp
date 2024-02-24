#include "fintamath/expressions/unary/NotExpr.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/FunctionUtils.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
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

using namespace detail;

NotExpr::NotExpr(ArgumentPtr inChild)
    : IUnaryExpressionCRTP(Not{}, std::move(inChild)) {
}

NotExpr::SimplifyFunctionVector NotExpr::getFunctionsForPreSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &NotExpr::nestedNotSimplify,
  };
  return simplifyFunctions;
}

NotExpr::SimplifyFunctionVector NotExpr::getFunctionsForPostSimplify() const {
  static const SimplifyFunctionVector simplifyFunctions = {
      &NotExpr::logicNegatableSimplify,
      &NotExpr::nestedNotSimplify,
  };
  return simplifyFunctions;
}

ArgumentPtr NotExpr::logicNegatableSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  const std::shared_ptr<const IExpression> rhsExpr = cast<IExpression>(rhs);

  if (!rhsExpr) {
    return {};
  }

  ArgumentPtr res;

  if (const auto op = cast<IOperator>(rhsExpr->getFunction());
      op && op->getPriority() == IOperator::Priority::Comparison) {

    res = makeExpr(*cast<IFunction>(getLogicOppositeFunction(*op)), rhsExpr->getChildren());
  }
  else if (is<Or>(rhsExpr->getFunction())) {
    ArgumentPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = notExpr(child);
    }

    res = andExpr(std::move(children));
  }
  else if (is<And>(rhsExpr->getFunction())) {
    ArgumentPtrVector children = rhsExpr->getChildren();

    for (auto &child : children) {
      child = notExpr(child);
    }

    res = orExpr(std::move(children));
  }

  return res;
}

ArgumentPtr NotExpr::nestedNotSimplify(const IFunction & /*func*/, const ArgumentPtr &rhs) {
  if (const auto expr = cast<NotExpr>(rhs)) {
    return expr->child;
  }

  return {};
}

std::shared_ptr<IFunction> NotExpr::getLogicOppositeFunction(const IFunction &function) {
  static const std::unordered_map<std::string, std::shared_ptr<IFunction>> nameToOppositeFunctionMap = {
      {Eqv{}.toString(), std::make_shared<Neqv>()},
      {Neqv{}.toString(), std::make_shared<Eqv>()},
      {More{}.toString(), std::make_shared<LessEqv>()},
      {Less{}.toString(), std::make_shared<MoreEqv>()},
      {MoreEqv{}.toString(), std::make_shared<Less>()},
      {LessEqv{}.toString(), std::make_shared<More>()},
  };
  return nameToOppositeFunctionMap.at(function.toString());
}

}
