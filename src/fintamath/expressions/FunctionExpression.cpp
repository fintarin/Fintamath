#include "fintamath/expressions/FunctionExpression.hpp"

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

FunctionExpression::FunctionExpression(const IFunction &function, const ArgumentsVector &args)
    : function(cast<IFunction>(function.clone())) {
  for (const auto &arg : args) {
    this->args.emplace_back(arg.get().clone());
  }
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
      std::vector<MathObjectPtr> values;
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

MathObjectPtr FunctionExpression::toMinimalObject() const {
  return std::make_unique<FunctionExpression>(*this);
}

const IFunction *FunctionExpression::getFunction() const {
  return function.get();
}

void FunctionExpression::setPrecision(uint8_t precision) {
}

MathObjectPtr FunctionExpression::simplify(bool isPrecise) const {
  return std::make_unique<FunctionExpression>(*this);
}

void FunctionExpression::validate() const {
}
}