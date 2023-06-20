#include "fintamath/expressions/FunctionExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const IFunction &inFunc, const ArgumentsPtrVector &inChildren)
    : func(cast<IFunction>(inFunc.clone())) {

  if (inChildren.size() != uint16_t(inFunc.getFunctionType())) {
    throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(inChildren));
  }

  for (const auto &child : inChildren) {
    children.emplace_back(child);
    compressChild(children.back());
  }
}

std::string FunctionExpression::toString() const {
  if (const auto oper = cast<IOperator>(func)) {
    if (oper->getOperatorPriority() == IOperator::Priority::PostfixUnary) {
      return postfixUnaryOperatorToString(*oper, children.front());
    }

    if (oper->getOperatorPriority() == IOperator::Priority::PrefixUnary) {
      return prefixUnaryOperatorToString(*oper, children.front());
    }

    return binaryOperatorToString(*oper, children.front(), children.back());
  }

  return functionToString(*func, children);
}

std::shared_ptr<IFunction> FunctionExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector FunctionExpression::getChildren() const {
  return children;
}

ArgumentPtr FunctionExpression::simplify() const {
  auto simpl = cast<FunctionExpression>(clone());

  for (auto &child : simpl->children) {
    simplifyChild(child);
  }

  if (ArgumentPtr res = callFunction(*simpl->func, simpl->children)) {
    return res;
  }

  return simpl;
}

ArgumentPtr FunctionExpression::preSimplify() const {
  auto simpl = cast<FunctionExpression>(clone());

  for (auto &child : simpl->children) {
    preSimplifyChild(child);
  }

  return simpl;
}

ArgumentPtr FunctionExpression::postSimplify() const {
  auto simpl = cast<FunctionExpression>(clone());
  ArgumentsRefVector args;

  for (auto &child : simpl->children) {
    postSimplifyChild(child);
    args.emplace_back(*child);
  }

  if (!func->doArgsMatch(args)) {
    return simpl;
  }

  return (*func)(args);
}

ArgumentPtr FunctionExpression::preciseSimplify() const {
  auto preciseExpr = cast<FunctionExpression>(clone());

  for (auto &child : preciseExpr->children) {
    preciseSimplifyChild(child);
  }

  return preciseExpr;
}

void FunctionExpression::setChildren(const ArgumentsPtrVector &childVect) {
  if (childVect.size() != size_t(func->getFunctionType())) {
    throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(childVect));
  }

  children = childVect;
}
}
