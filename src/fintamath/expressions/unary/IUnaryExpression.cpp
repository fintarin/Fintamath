#include "fintamath/expressions/IUnaryExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

string IUnaryExpression::toString() const {
  if (!func) {
    return {};
  }

  if (const auto oper = cast<IOperator>(func)) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixToString();
    default:
      return prefixToString();
    }
  }

  return functionToString();
}

string IUnaryExpression::postfixToString() const {
  string result = child->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + func->toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(child); comp && *comp < ZERO) {
    return putInBrackets(result) + func->toString();
  }

  return result + func->toString();
}

string IUnaryExpression::prefixToString() const {
  string result = func->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority == IOperator::Priority::PrefixUnary || priority == IOperator::Priority::Multiplication ||
          priority == IOperator::Priority::Exponentiation) {
        return result + child->toString();
      }

      return result + putInBrackets(child->toString());
    }
  }

  return result + child->toString();
}

string IUnaryExpression::functionToString() const {
  return func->toString() + "(" + child->toString() + ")";
}

shared_ptr<IFunction> IUnaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IUnaryExpression::getChildren() const {
  return {child};
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

  return simpl;
}

ArgumentPtr IUnaryExpression::postSimplify() const {
  auto simpl = cast<IUnaryExpression>(clone());
  postSimplifyChild(simpl->child);

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->child})) {
    return res;
  }

  return simpl;
}

void IUnaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 1) {
    return;
  }

  child = childVect.front();
}

}