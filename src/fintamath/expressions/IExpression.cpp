#include "fintamath/expressions/IExpression.hpp"

#include "fintamath/expressions/Expression.hpp" // TODO: remove this include
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Real.hpp"

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

std::string IExpression::putInBrackets(const std::string &str) {
  return "(" + str + ")";
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

void IExpression::simplifyConstant(bool isPrecise, MathObjectPtr &obj) {
  if (auto expr = cast<IExpression>(std::move(obj))) {
    obj = expr->simplify(isPrecise);
    return;
  }

  if (is<IConstant>(obj)) {
    auto constant = cast<IConstant>(std::move(obj));
    auto constVal = (*constant)();

    if (const auto *num = cast<INumber>(constVal.get()); num && !num->isPrecise() && isPrecise) {
      obj = std::move(constant);
    } else {
      obj = std::move(constVal);
    }

    return;
  }

  obj = obj->toMinimalObject();
}

void IExpression::setPrecisionMathObject(uint8_t precision, MathObjectPtr &obj) {
  if (is<INumber>(obj)) {
    obj = convert<Real>(*obj).precise(precision).clone();
    return;
  }
  if (is<IExpression>(obj)) {
    auto copyExpr = cast<IExpression>(std::move(obj));
    copyExpr->setPrecision(precision);
    obj = std::move(copyExpr);
  }
}

}
