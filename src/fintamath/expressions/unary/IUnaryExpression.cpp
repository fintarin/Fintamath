#include "fintamath/expressions/IUnaryExpression.hpp"

#include "fintamath/core/IComparable.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

std::string IUnaryExpression::toString() const {
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

// TODO: move to ExpressionsUtils
std::string IUnaryExpression::postfixToString() const {
  std::string result = child->toString();

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

// TODO: move to ExpressionsUtils
std::string IUnaryExpression::prefixToString() const {
  std::string result = func->toString();

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

std::string IUnaryExpression::functionToString() const {
  return func->toString() + putInBrackets(child->toString());
}

std::shared_ptr<IFunction> IUnaryExpression::getFunction() const {
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

  if (auto res = simpl->globalSimplify()) {
    return res;
  }

  return simpl;
}

ArgumentPtr IUnaryExpression::postSimplify() const {
  auto simpl = cast<IUnaryExpression>(clone());
  postSimplifyChild(simpl->child);

  if (ArgumentPtr res = callFunction(*simpl->func, {simpl->child})) {
    return res;
  }

  if (auto res = simpl->globalSimplify()) {
    return res;
  }

  return simpl;
}

IUnaryExpression::SimplifyFunctionsVector IUnaryExpression::getFunctionsForSimplify() const {
  return {};
}

ArgumentPtr IUnaryExpression::globalSimplify() const {
  auto simpl = cast<IUnaryExpression>(clone());
  const SimplifyFunctionsVector simplFunctions = getFunctionsForSimplify();

  for (const auto &simplFunc : simplFunctions) {
    if (auto res = simplFunc(simpl->child)) {
      return res;
    }
  }

  return {};
}

void IUnaryExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != 1) {
    std::vector<std::string> argNamesVect(childVect.size());

    for (size_t i = 0; i < argNamesVect.size(); i++) {
      argNamesVect[i] = childVect[i].get()->toString();
    }

    throw InvalidInputFunctionException(toString(), argNamesVect);
  }

  child = childVect.front();
}

}