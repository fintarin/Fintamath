#include "fintamath/expressions/interfaces/IUnaryExpression.hpp"

#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/FunctionArguments.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

IUnaryExpression::IUnaryExpression(const IFunction &inFunc, ArgumentPtr rhs)
    : func(cast<IFunction>(inFunc.clone())),
      child(std::move(rhs)) {
}

std::string IUnaryExpression::toString() const {
  if (const auto oper = cast<IOperator>(func)) {
    if (oper->getOperatorPriority() == IOperator::Priority::PostfixUnary) {
      return postfixUnaryOperatorToString(*oper, child);
    }

    return prefixUnaryOperatorToString(*oper, child);
  }

  return functionToString(*func, {child});
}

const std::shared_ptr<IFunction> &IUnaryExpression::getFunction() const {
  return func;
}

const ArgumentPtrVector &IUnaryExpression::getChildren() const {
  childrenCached.front() = child;
  return childrenCached;
}

IUnaryExpression::SimplifyFunctionVector IUnaryExpression::getFunctionsForPreSimplify() const {
  return {};
}

IUnaryExpression::SimplifyFunctionVector IUnaryExpression::getFunctionsForPostSimplify() const {
  return {};
}

ArgumentPtr IUnaryExpression::preSimplify() const {
  const auto simpl = cast<IUnaryExpression>(clone());
  preSimplifyChild(simpl->child);
  return simpl->simplifyRec(false);
}

ArgumentPtr IUnaryExpression::postSimplify() const {
  const auto simpl = cast<IUnaryExpression>(clone());
  postSimplifyChild(simpl->child);
  return simpl->simplifyRec(true);
}

ArgumentPtr IUnaryExpression::simplifyRec(const bool isPostSimplify) const {
  if (ArgumentPtr res = simplifyUndefined(*func, child)) {
    return res;
  }

  if (ArgumentPtr res = callFunction(*func, {child})) {
    return res;
  }

  ArgumentPtr res = isPostSimplify ? useSimplifyFunctions(getFunctionsForPostSimplify(),
                                                          *func,
                                                          child)
                                   : useSimplifyFunctions(getFunctionsForPreSimplify(),
                                                          *func,
                                                          child);

  if (res && *res != *this) {
    if (isPostSimplify) {
      postSimplifyChild(res);
    }
    else {
      preSimplifyChild(res);
    }

    return res;
  }

  return clone();
}

void IUnaryExpression::setChildren(const ArgumentPtrVector &childVect) {
  if (childVect.size() != 1) {
    throw InvalidInputFunctionException(toString(), argumentVectorToStringVector(childVect));
  }

  child = childVect.front();
}

}