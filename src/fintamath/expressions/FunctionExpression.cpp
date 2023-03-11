#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

FunctionExpression::FunctionExpression(const FunctionExpression &rhs)
    : function(cast<IFunction>(rhs.function->clone())) {
  for (const auto &arg : rhs.args) {
    args.emplace_back(arg->clone());
  }
}

FunctionExpression &FunctionExpression::operator=(const FunctionExpression &rhs) {
  if (&rhs != this) {
    function = cast<IFunction>(rhs.function->clone());

    for (const auto &arg : rhs.args) {
      args.emplace_back(arg->clone());
    }
  }

  return *this;
}

FunctionExpression::FunctionExpression(const IFunction &function, ArgumentsPtrVector &&args)
    : function(cast<IFunction>(function.clone())),
      args(std::move(args)) {
}

std::string FunctionExpression::toString() const {
  if (const auto *oper = cast<IOperator>(function.get())) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixUnaryOperatorToString(*oper, args.front());
    default:
      std::vector<std::unique_ptr<IMathObject>> values;
      values.emplace_back(args.front()->clone());
      values.emplace_back(args.back()->clone());
      return binaryOperatorToString(*oper, values);
    }
  }

  return functionToString();
}

std::string FunctionExpression::functionToString() const {
  static const std::string delimiter = ", ";

  std::string result = function->toString() + "(";

  for (const auto &arg : args) {
    result += arg->toString() + delimiter;
  }

  result = result.substr(0, result.length() - delimiter.length()) + ")";

  return result;
}

const IFunction *FunctionExpression::getFunction() const {
  return function.get();
}

void FunctionExpression::setPrecision(uint8_t precision) {
  for (auto &arg : args) {
    setMathObjectPrecision(arg, precision);
  }
}

std::unique_ptr<IMathObject> FunctionExpression::simplify(bool isPrecise) const {
  const auto &func = cast<IFunction>(*function.get());

  ArgumentsVector arguments;
  bool canCallFunction = true;

  for (const auto &arg : args) {
    const auto *child = arg.get();

    if (!child) {
      continue;
    }

    if (is<Variable>(child) || is<IConstant>(child) || is<IExpression>(child)) {
      canCallFunction = false;
    }

    arguments.emplace_back(*child);
  }

  if (!canCallFunction) {
    return std::make_unique<FunctionExpression>(*this);
  }

  auto countResult = func(arguments);

  if (const auto *num = cast<INumber>(countResult.get()); num && !num->isPrecise() && isPrecise) {
    return std::make_unique<FunctionExpression>(*this);
  }

  return countResult;
}

void FunctionExpression::validate() const {
  ArgumentsVector newArgs;

  for (const auto &arg : args) {
    if (const auto *argExpr = cast<IExpression>(arg.get())) {
      argExpr->validate();
    }

    newArgs.emplace_back(*arg);
  }

  validateArgs(*function, newArgs);
}

IMathObject *FunctionExpression::simplify() {
  const auto &func = *function;

  ArgumentsVector arguments;
  bool canCallFunction = true;

  for (const auto &arg : args) {
    const auto *child = arg.get();

    if (!child) {
      continue;
    }

    if (is<Variable>(child) || is<IConstant>(child) || is<IExpression>(child)) {
      canCallFunction = false;
    }

    arguments.emplace_back(*child);
  }

  if (!canCallFunction) {
    return this;
  }

  auto countResult = func(arguments);

  if (const auto *num = cast<INumber>(countResult.get()); num && !num->isPrecise()) {
    return this;
  }

  return countResult.release();
}
}