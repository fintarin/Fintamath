#include "fintamath/expressions/FunctionExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const IFunction &inFunc, const ArgumentPtrVector &inChildren)
    : func(cast<IFunction>(inFunc.clone())) {

  for (const auto &child : inChildren) {
    children.emplace_back(child);
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

const std::shared_ptr<IFunction> &FunctionExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &FunctionExpression::getChildren() const {
  return children;
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
  ArgumentRefVector args;

  for (auto &child : simpl->children) {
    postSimplifyChild(child);
    args.emplace_back(*child);
  }

  if (!func->doArgsMatch(args)) {
    return simpl;
  }

  return callFunction(*simpl->func, argumentRefVectorToArgumentPtrVector(args));
}

void FunctionExpression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.size() != size_t(func->getFunctionType())) {
    throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(childVect));
  }

  children = childVect;
}
}
