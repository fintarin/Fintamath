#include "fintamath/expressions/FunctionExpression.hpp"

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const IFunction &inFunc, ArgumentPtrVector inChildren)
    : func(cast<IFunction>(inFunc.clone())) {

  for (auto &&child : std::move(inChildren)) {
    children.emplace_back(std::move(child));
  }
}

std::string FunctionExpression::toString() const {
  if (const auto oper = cast<IOperator>(func)) {
    if (oper->getPriority() == IOperator::Priority::PostfixUnary) {
      return postfixUnaryOperatorToString(*oper, children.front());
    }

    if (oper->getPriority() == IOperator::Priority::PrefixUnary) {
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
  if (childVect.size() != func->getArgumentTypes().size()) {
    throw InvalidInputFunctionException(func->toString(), argumentVectorToStringVector(childVect));
  }

  children = childVect;
}
}
