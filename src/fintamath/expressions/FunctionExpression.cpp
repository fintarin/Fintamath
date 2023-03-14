#include "fintamath/expressions/FunctionExpression.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
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

// void FunctionExpression::setPrecision(uint8_t precision) {
//   for (auto &arg : children) {
//     setMathObjectPrecision(arg, precision);
//   }
// }

// unique_ptr<IMathObject> FunctionExpression::simplify(bool isPrecise) const {
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
//   return make_unique<FunctionExpression>(*this);
// }

// auto countResult = (*function)(arguments);

// if (const auto *num = cast<INumber>(countResult); num && !num->isPrecise() && isPrecise) {
//   return make_unique<FunctionExpression>(*this);
// }

// return countResult;
// }

shared_ptr<IMathObject> FunctionExpression::simplify() {
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

  shared_ptr<IMathObject> res = (*func)(arguments);

  if (const auto num = cast<INumber>(res); num && !num->isPrecise()) {
    return {};
  }

  return res;
}

}
