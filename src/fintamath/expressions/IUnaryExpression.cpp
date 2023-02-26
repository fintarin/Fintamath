#include "fintamath/expressions/IUnaryExpression.hpp"

namespace fintamath {

IUnaryExpression &IUnaryExpression::operator=(const IUnaryExpression &rhs) {
  if (&rhs != this) {
    if (rhs.info) {
      info = rhs.info->clone();
    } else {
      info = nullptr;
    }
  }
  return *this;
}

void IUnaryExpression::setPrecision(uint8_t precision) {
  if (is<IExpression>(info)) {
    auto expr = cast<IExpression>(std::move(info));
    expr->setPrecision(precision);
    info = std::move(expr);
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

  if (const auto *oper = cast<IOperator>(func)) {
    if (oper->getOperatorPriority() == IOperator::Priority::PostfixUnary) {
      return postfixToString(*func);
    }

    return prefixToString(*func);
  }

  return functionToString(*func);
}

std::string IUnaryExpression::postfixToString(const IFunction &oper) const {
  std::string result = info->toString();

  if (const auto *child = cast<IExpression>(info.get())) {
    if (const auto *exprOper = cast<IOperator>(child->getFunction())) {
      if (auto priority = exprOper->getOperatorPriority(); priority != IOperator::Priority::PostfixUnary) {
        return this->putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto *comp = cast<IComparable>(info.get()); comp && *comp < ZERO) {
    return this->putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

std::string IUnaryExpression::prefixToString(const IFunction &oper) const {
  std::string result = oper.toString();
  if (const auto *child = cast<IExpression>(info.get())) {
    if (const auto *exprOper = cast<IOperator>(child->getFunction())) {
      if (auto priority = exprOper->getOperatorPriority(); priority != IOperator::Priority::PrefixUnary) {
        if (priority == IOperator::Priority::Multiplication) {
          return result + info->toString();
        }

        // TODO: refactor this when PowExpression will be implemented
        if (const auto *childExpr = cast<Expression>(child)) {
          if (is<Pow>(childExpr->getFunction())) {
            return result + info->toString();
          }
        }

        return result + this->putInBrackets(info->toString());
      }
    }
  }

  return result + info->toString();
}

std::string IUnaryExpression::functionToString(const IFunction &oper) const {
  return oper.toString() + "(" + info->toString() + ")";
}

void IUnaryExpression::simplifyValue(bool isPrecise) {
  if (is<IExpression>(info)) {
    auto expr = cast<IExpression>(std::move(info));
    info = expr->simplify(isPrecise);
    return;
  }

  if (is<IConstant>(info)) {
    auto constant = cast<IConstant>(std::move(info));
    auto constVal = (*constant)();

    if (const auto *num = cast<INumber>(constVal.get()); num && isPrecise && !num->isPrecise()) {
      info = std::move(constant);
    } else {
      info = std::move(constVal);
    }

    return;
  }

  info = info->simplify();
}

}