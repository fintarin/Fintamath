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
  if (!func) {
    return {};
  }

  if (const auto oper = cast<IOperator>(func)) {
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
        return putInBrackets(result) + func->toString();
      }
    }
  }

  if (const auto comp = cast<IComparable>(child); comp && *comp < ZERO) {
    return putInBrackets(result) + func->toString();
  }

  return result + func->toString();
}

std::string IUnaryExpression::prefixToString() const {
  std::string result = func->toString();

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
  return func->toString() + "(" + child->toString() + ")";
}

void IUnaryExpression::simplifyValue(bool isPrecise) {
  IExpression::simplifyChild(child);
}

std::shared_ptr<IMathObject> IUnaryExpression::preSimplify() const {
  return {};
}

std::shared_ptr<IMathObject> IUnaryExpression::postSimplify() const {
  return {};
}

std::shared_ptr<IMathObject> IUnaryExpression::simplify() {
  if (auto res = preSimplify()) {
    simplifyChild(res);
    return res;
  }

  simplifyChild(child);

  if (func->isNonExressionEvaluatable() && func->doArgsMatch({*child})) {
    return (*func)(*child);
  }

  if (auto res = preSimplify()) { // TODO: try to remove this
    return res;
  }

  if (auto res = postSimplify()) {
    return res;
  }

  return {};
}

void IUnaryExpression::validate() const {
  if (const auto childExpr = cast<IExpression>(child)) {
    childExpr->validate();
  }

  validateChildren(*func, {child});
}

std::shared_ptr<IFunction> IUnaryExpression::getFunction() const {
  return func;
}

ArgumentsPtrVector IUnaryExpression::getChildren() const {
  return {child};
}

}