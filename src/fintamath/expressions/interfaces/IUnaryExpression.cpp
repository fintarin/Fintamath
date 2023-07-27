#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/literals/constants/Undefined.hpp"

namespace fintamath {

std::string IUnaryExpression::toString() const {
  if (const auto oper = cast<IOperator>(func)) {
    if (oper->getOperatorPriority() == IOperator::Priority::PostfixUnary) {
      return postfixUnaryOperatorToString(*oper, child);
    }

    return prefixUnaryOperatorToString(*oper, child);
  }

  return functionToString(*func, {child});
}

std::shared_ptr<IFunction> IUnaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IUnaryExpression::getChildren() const {
  return {child};
}

IUnaryExpression::SimplifyFunctionsVector IUnaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IUnaryExpression::SimplifyFunctionsVector IUnaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

ArgumentPtr IUnaryExpression::simplify() const {
  ArgumentPtr simpl = cast<IUnaryExpression>(clone());
  preSimplifyChild(simpl);
  postSimplifyChild(simpl);
  return simpl;
}

ArgumentPtr IUnaryExpression::preSimplify() const {
  auto simpl = cast<IUnaryExpression>(clone());
  preSimplifyChild(simpl->child);

  if (is<Undefined>(simpl->child)) {
    return Undefined().clone();
  }

  ArgumentPtr res = simpl->useSimplifyFunctions(getFunctionsForPreSimplify());

  if (res && *res != *simpl) {
    preSimplifyChild(res);
    return res;
  }

  return simpl;
}

ArgumentPtr IUnaryExpression::postSimplify() const {
  auto simpl = cast<IUnaryExpression>(clone());
  postSimplifyChild(simpl->child);

  if (is<Undefined>(simpl->child)) {
    return Undefined().clone();
  }

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->child})) {
    return res;
  }

  ArgumentPtr res = simpl->useSimplifyFunctions(getFunctionsForPostSimplify());

  if (res && *res != *simpl) {
    postSimplifyChild(res);
    return res;
  }

  return simpl;
}

ArgumentPtr IUnaryExpression::preciseSimplify() const {
  auto preciseExpr = cast<IUnaryExpression>(clone());
  preciseSimplifyChild(preciseExpr->child);
  return preciseExpr;
}

ArgumentPtr IUnaryExpression::useSimplifyFunctions(const SimplifyFunctionsVector &simplFuncs) const {
  for (const auto &simplFunc : simplFuncs) {
    if (auto res = simplFunc(*func, child)) {
      return res;
    }
  }

  return {};
}

void IUnaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 1) {
    throw InvalidInputFunctionException(toString(), argumentVectorToStringVector(childVect));
  }

  child = childVect.front();
}

}