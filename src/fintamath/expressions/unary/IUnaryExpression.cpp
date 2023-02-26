#include "fintamath/expressions/unary/IUnaryExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/binary/PowExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/functions/powers/Pow.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

IUnaryExpression::IUnaryExpression(const IUnaryExpression &rhs)
    : function(cast<IFunction>(rhs.function->clone())),
      info(rhs.info->clone()) {
}

IUnaryExpression::IUnaryExpression(MathObjectPtr &&rhs) : info(std::move(rhs)) {
}

IUnaryExpression &IUnaryExpression::operator=(const IUnaryExpression &rhs) {
  if (&rhs != this) {
    info = rhs.info->clone();
    function = cast<IFunction>(rhs.function->clone());
  }

  return *this;
}

void IUnaryExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(info.get())) {
    expr->setPrecision(precision);
    return;
  }

  if (const auto *constant = cast<IConstant>(info.get())) {
    info = (*constant)();
  }

  if (is<INumber>(info)) {
    info = convert<Real>(*info).precise(precision).clone();
  }
}

std::string IUnaryExpression::toString() const {
  const auto *func = this->getFunction();

  if (!func) {
    return {};
  }

  if (const auto *oper = cast<IOperator>(func)) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixToString(*func);
    default:
      return prefixToString(*func);
    }
  }

  return functionToString(*func);
}

std::string IUnaryExpression::postfixToString(const IFunction &oper) const {
  std::string result = info->toString();

  if (const auto *child = cast<IExpression>(info.get())) {
    if (const auto *exprOper = cast<IOperator>(child->getFunction())) {
      if (auto priority = exprOper->getOperatorPriority(); priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto *comp = cast<IComparable>(info.get()); comp && *comp < ZERO) {
    return putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

std::string IUnaryExpression::prefixToString(const IFunction &oper) const {
  std::string result = oper.toString();

  if (const auto *child = cast<IExpression>(info.get())) {
    if (const auto *exprOper = cast<IOperator>(child->getFunction())) {
      auto priority = exprOper->getOperatorPriority();

      if (priority == IOperator::Priority::PrefixUnary || priority == IOperator::Priority::Multiplication ||
          priority == IOperator::Priority::Exponentiation) {
        return result + info->toString();
      }

      return result + putInBrackets(info->toString());
    }
  }

  return result + info->toString();
}

std::string IUnaryExpression::functionToString(const IFunction &oper) const {
  return oper.toString() + "(" + info->toString() + ")";
}

void IUnaryExpression::simplifyValue(bool isPrecise) {
  IExpression::simplifyValue(isPrecise, info);
}

void IUnaryExpression::validate() const {
  // TODO: implement it
}

MathObjectPtr IUnaryExpression::getInfo() const {
  return info->clone();
}

const IFunction *IUnaryExpression::getFunction() const {
  return function.get();
}

}