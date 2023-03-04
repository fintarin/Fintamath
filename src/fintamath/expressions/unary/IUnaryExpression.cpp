#include "fintamath/expressions/unary/IUnaryExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
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
      child(rhs.child->clone()) {
}

IUnaryExpression::IUnaryExpression(MathObjectPtr &&rhs) : child(std::move(rhs)) {
}

IUnaryExpression &IUnaryExpression::operator=(const IUnaryExpression &rhs) {
  if (&rhs != this) {
    child = rhs.child->clone();
    function = cast<IFunction>(rhs.function->clone());
  }

  return *this;
}

void IUnaryExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(child.get())) {
    expr->setPrecision(precision);
    return;
  }

  if (const auto *constant = cast<IConstant>(child.get())) {
    child = (*constant)();
  }

  if (is<INumber>(child)) {
    child = convert<Real>(*child).precise(precision).clone();
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
  std::string result = child->toString();

  if (const auto *childExpr = cast<IExpression>(child.get())) {
    if (const auto *exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (auto priority = exprOper->getOperatorPriority(); priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto *comp = cast<IComparable>(child.get()); comp && *comp < ZERO) {
    return putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

std::string IUnaryExpression::prefixToString(const IFunction &oper) const {
  std::string result = oper.toString();

  if (const auto *childExpr = cast<IExpression>(child.get())) {
    if (const auto *exprOper = cast<IOperator>(childExpr->getFunction())) {
      auto priority = exprOper->getOperatorPriority();

      if (priority == IOperator::Priority::PrefixUnary || priority == IOperator::Priority::Multiplication ||
          priority == IOperator::Priority::Exponentiation) {
        return result + child->toString();
      }

      return result + putInBrackets(child->toString());
    }
  }

  return result + child->toString();
}

std::string IUnaryExpression::functionToString(const IFunction &oper) const {
  return oper.toString() + "(" + child->toString() + ")";
}

void IUnaryExpression::simplifyValue(bool isPrecise) {
  IExpression::simplifyExpr(child);
}

void IUnaryExpression::validate() const {
  // TODO: implement it
}

MathObjectPtr IUnaryExpression::getInfo() const {
  return child->clone();
}

const IFunction *IUnaryExpression::getFunction() const {
  return function.get();
}

}