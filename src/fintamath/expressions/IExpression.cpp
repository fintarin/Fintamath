#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"
#include <memory>

namespace fintamath {

void IExpression::validateArgs(const IFunction &func, const ArgumentsVector &args) const {
  const ArgumentsTypesVector argsTypes = func.getArgsTypes();

  if (argsTypes.size() != args.size()) {
    throw InvalidInputException(toString());
  }

  for (size_t i = 0; i < args.size(); i++) {
    const auto *child = &args[i].get();
    const auto &type = argsTypes[i];

    if (is<Variable>(child)) {
      continue;
    }

    if (const auto *childConst = cast<IConstant>(child)) {
      const std::type_info &childType = childConst->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType)) {
        throw InvalidInputException(toString());
      }

      continue;
    }

    if (const auto *childExpr = cast<IExpression>(child)) {
      const auto *childFunc = childExpr->getFunction();

      if (!childFunc) {
        continue;
      }

      const std::type_info &childType = childFunc->getReturnType();

      if (!InheritanceTable::isBaseOf(type, childType) && !InheritanceTable::isBaseOf(childType, type)) {
        throw InvalidInputException(toString());
      }

      continue;
    }

    if (!InheritanceTable::isBaseOf(type, typeid(*child))) {
      throw InvalidInputException(toString());
    }
  }
}

MathObjectPtr IExpression::toMinimalObject() const {
  auto copyExpr = clone();
  simplifyExpr(copyExpr); // TODO: enable when simplify will be implemented finally
  return copyExpr;
}

std::string IExpression::binaryOperatorToString(const IOperator &oper, const std::vector<MathObjectPtr> &values) {
  std::string result;

  std::string operStr = oper.toString();
  IOperator::Priority operPriority = oper.getOperatorPriority();
  bool operIsAssociative = oper.isAssociative();

  if (operPriority != IOperator::Priority::Multiplication && operPriority != IOperator::Priority::Exponentiation) {
    operStr = ' ' + operStr + ' ';
  }

  for (size_t i = 0; i < values.size(); i++) {
    const auto &child = values[i];

    bool shouldPutInBrackets = false;

    if (const auto *childExpr = cast<IExpression>(child.get())) {
      if (const auto *childOper = cast<IOperator>(childExpr->getFunction())) {
        if (auto priority = childOper->getOperatorPriority();
            priority > operPriority || (priority == operPriority && !operIsAssociative && i > 0)) {
          shouldPutInBrackets = true;
        }
      }
    }

    if (shouldPutInBrackets) {
      result += putInBrackets(child->toString());
    } else {
      result += child->toString();
    }

    result += operStr;
  }

  result = result.substr(0, result.length() - operStr.length());

  return result;
}

std::string IExpression::postfixUnaryOperatorToString(const IOperator &oper, const MathObjectPtr &lhs) {
  std::string result = lhs->toString();

  if (const auto *child = cast<IExpression>(lhs.get())) {
    if (const auto *childOper = cast<IOperator>(child->getFunction())) {
      if (auto priority = childOper->getOperatorPriority(); priority != IOperator::Priority::PostfixUnary) {
        return putInBrackets(result) + oper.toString();
      }
    }
  }

  if (const auto *comp = cast<IComparable>(lhs.get()); comp && *comp < ZERO) {
    return putInBrackets(result) + oper.toString();
  }

  return result + oper.toString();
}

void IExpression::simplifyExpr(MathObjectPtr &obj) {
  if (auto *exprObj = cast<IExpression>(obj.get())) {
    if (auto *simplObj = exprObj->simplify(); simplObj && simplObj != obj.get()) {
      obj = MathObjectPtr(simplObj);
    }
  }
}

void IExpression::setMathObjectPrecision(MathObjectPtr &obj, uint8_t precision) {
  if (is<INumber>(obj)) {
    obj = convert<Real>(*obj).precise(precision).clone();
    return;
  }

  if (auto *expr = cast<IExpression>(obj.get())) {
    expr->setPrecision(precision);
    return;
  }
}

}
