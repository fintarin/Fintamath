#include "fintamath/expressions/unary/IUnaryExpression.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
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

IUnaryExpression &IUnaryExpression::operator=(const IUnaryExpression &rhs) {
  if (&rhs != this) {
    function = cast<IFunction>(rhs.function->clone());
    child = rhs.child->clone();
  }

  return *this;
}

IUnaryExpression::IUnaryExpression(const IFunction &func, std::shared_ptr<IMathObject> arg)
    : function(cast<IFunction>(func.clone())),
      child(std::move(arg)) {
}

void IUnaryExpression::setPrecision(uint8_t precision) {
  if (const auto expr = cast<IExpression>(child)) {
    expr->setPrecision(precision);
    return;
  }

  if (const auto constant = cast<IConstant>(child)) {
    child = (*constant)();
  }

  if (is<INumber>(child)) {
    child = std::make_shared<Real>(convert<Real>(*child).precise(precision));
  }
}

std::string IUnaryExpression::toString() const {
  if (!function) {
    return {};
  }

  if (const auto oper = cast<IOperator>(function)) {
    switch (oper->getOperatorPriority()) {
    case IOperator::Priority::PostfixUnary:
      return postfixToString();
    default:
      return prefixToString();
    }
  }

  return functionToString();
}

std::string IUnaryExpression::postfixToString() const {
  std::string result = child->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + function->toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(child); comp && *comp < ZERO) {
    return putInBrackets(result) + function->toString();
  }

  return result + function->toString();
}

std::string IUnaryExpression::prefixToString() const {
  std::string result = function->toString();

  if (const auto childExpr = cast<IExpression>(child)) {
    if (const auto exprOper = cast<IOperator>(childExpr->getFunction())) {
      if (IOperator::Priority priority = exprOper->getOperatorPriority();
          priority == IOperator::Priority::PrefixUnary || priority == IOperator::Priority::Multiplication ||
          priority == IOperator::Priority::Exponentiation) {
        return result + child->toString();
      }

      return result + putInBrackets(child->toString());
    }
  }

  return result + child->toString();
}

std::string IUnaryExpression::functionToString() const {
  return function->toString() + "(" + child->toString() + ")";
}

void IUnaryExpression::simplifyValue(bool isPrecise) {
  IExpression::simplifyExpr(child);
}

void IUnaryExpression::validate() const {
  validateArgs(*function, {child});
}

void IUnaryExpression::compress() {
  if (const auto expr = cast<Expression>(child)) {
    child = expr->getChild();
  }
}

std::shared_ptr<IFunction> IUnaryExpression::getFunction() const {
  return function;
}

std::shared_ptr<IMathObject> IUnaryExpression::getChild() const {
  return child;
}

}