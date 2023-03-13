#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const FunctionExpression &rhs)
    : func(cast<IFunction>(rhs.func->clone())) {
  for (const auto &arg : rhs.children) {
    children.emplace_back(arg->clone());
  }
}

FunctionExpression &FunctionExpression::operator=(const FunctionExpression &rhs) {
  if (&rhs != this) {
    func = cast<IFunction>(rhs.func->clone());

    for (const auto &arg : rhs.children) {
      children.emplace_back(arg->clone());
    }
  }

  return *this;
}

FunctionExpression::FunctionExpression(const IFunction &function, ArgumentsPtrVector children)
    : func(cast<IFunction>(function.clone())),
      children(std::move(children)) {
}

std::string FunctionExpression::toString() const {
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

std::string FunctionExpression::functionToString() const {
  static const std::string delimiter = ", ";

  std::string result = func->toString() + "(";

  for (const auto &arg : children) {
    result += arg->toString() + delimiter;
  }

  result = result.substr(0, result.length() - delimiter.length()) + ")";

  return result;
}

std::shared_ptr<IFunction> FunctionExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector FunctionExpression::getChildren() const {
  return children;
}

void FunctionExpression::setPrecision(uint8_t precision) {
  for (auto &arg : children) {
    setMathObjectPrecision(arg, precision);
  }
}

std::unique_ptr<IMathObject> FunctionExpression::simplify(bool isPrecise) const {
  // ArgumentsRefVector arguments;
  // bool canCallFunction = true;

  // for (const auto &arg : args) {
  //   const auto *child = arg;

  //   if (!child) {
  //     continue;
  //   }

  //   if (is<Variable>(child) || is<IConstant>(child) || is<IExpression>(child)) {
  //     canCallFunction = false;
  //   }

  //   arguments.emplace_back(*child);
  // }

  // if (!canCallFunction) {
  //   return std::make_unique<FunctionExpression>(*this);
  // }

  // auto countResult = (*function)(arguments);

  // if (const auto *num = cast<INumber>(countResult); num && !num->isPrecise() && isPrecise) {
  //   return std::make_unique<FunctionExpression>(*this);
  // }

  // return countResult;

  return std::make_unique<FunctionExpression>(*this);
}

void FunctionExpression::validate() const {
  validateChildren(*func, children);

  for (const auto &arg : children) {
    if (const auto argExpr = cast<IExpression>(arg)) {
      argExpr->validate();
    }
  }
}

std::shared_ptr<IMathObject> FunctionExpression::simplify() {
  if (!func->isNonExressionEvaluatable()) {
    return {};
  }

  ArgumentsRefVector arguments;

  for (auto &child : children) {
    simplifyChild(child);
    arguments.emplace_back(*child);
  }

  if (!func->doArgsMatch(arguments)) {
    return {};
  }

  std::shared_ptr<IMathObject> res = (*func)(arguments);

  if (const auto num = cast<INumber>(res); num && !num->isPrecise()) {
    return {};
  }

  return res;
}

}
