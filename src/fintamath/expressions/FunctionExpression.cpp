#include "fintamath/expressions/FunctionExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const IFunction &function, const ArgumentsPtrVector &children)
    : func(cast<IFunction>(function.clone())) {

  for (const auto &child : children) {
    if (const auto expr = cast<IExpression>(child); expr && !expr->getFunction()) {
      this->children.emplace_back(expr->getChildren().front());
    }
    else {
      this->children.emplace_back(child);
    }
  }
}

string FunctionExpression::toString() const {
  if (const auto oper = cast<IOperator>(func)) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixUnaryOperatorToString(*oper, children.front());
    default:
      ArgumentsPtrVector values;
      values.emplace_back(children.front());
      values.emplace_back(children.back());
      return binaryOperatorToString(*oper, values);
    }
  }

  return functionToString();
}

string FunctionExpression::functionToString() const {
  static const string delimiter = ", ";

  string result = func->toString() + "(";

  for (const auto &arg : children) {
    result += arg->toString() + delimiter;
  }

  result = result.substr(0, result.length() - delimiter.length()) + ")";

  return result;
}

shared_ptr<IFunction> FunctionExpression::getFunction() const {
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

  if (!func->isNonExressionEvaluatable() || !func->doArgsMatch(args)) {
    return simpl;
  }

  ArgumentPtr val = (*func)(args);

  if (const auto num = cast<INumber>(val); num && !num->isPrecise()) {
    return simpl;
  }

  return val;
}

}
