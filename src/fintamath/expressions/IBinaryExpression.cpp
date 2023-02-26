#include "fintamath/expressions/IBinaryExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IBinaryExpression &rhs)
    : lhsInfo(rhs.lhsInfo->clone()),
      rhsInfo(rhs.rhsInfo->clone()) {
}

IBinaryExpression::IBinaryExpression(const IMathObject &lhs, const IMathObject &rhs)
    : lhsInfo(lhs.clone()),
      rhsInfo(rhs.clone()) {
}

IBinaryExpression::IBinaryExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : lhsInfo(std::move(lhs)),
      rhsInfo(std::move(rhs)) {
}

IBinaryExpression &IBinaryExpression::operator=(const IBinaryExpression &rhs) {
  if (&rhs != this) {
    if (rhs.lhsInfo && rhs.rhsInfo) {
      lhsInfo = rhs.lhsInfo->clone();
      rhsInfo = rhs.rhsInfo->clone();
    } else {
      lhsInfo = nullptr;
      rhsInfo = nullptr;
    }
  }
  return *this;
}

void IBinaryExpression::setPrecision(uint8_t precision) {
  // TODO: implement it
}

std::string IBinaryExpression::toString() const {
  std::string result;

  const auto *parentOper = cast<IOperator>(getFunction());
  std::string parentOperStr = parentOper->toString();
  IOperator::Priority parentOperPriority = parentOper->getOperatorPriority();
  bool parentOperIsAssociative = parentOper->isAssociative();

  if (parentOperPriority != IOperator::Priority::Multiplication &&
      parentOperPriority != IOperator::Priority::Exponentiation) {
    parentOperStr = ' ' + parentOperStr + ' ';
  }

  auto children = std::vector<MathObjectPtr>();
  children.emplace_back(lhsInfo->clone());
  children.emplace_back(rhsInfo->clone());

  for (size_t i = 0; i < children.size(); i++) {
    const auto &child = children[i];

    bool shouldPutInBrackets = false;

    if (const auto *childExpr = cast<IExpression>(child.get())) {
      if (const auto *oper = cast<IOperator>(childExpr->getFunction())) {
        if (auto priority = oper->getOperatorPriority();
            priority > parentOperPriority || (priority == parentOperPriority && !parentOperIsAssociative && i > 0)) {
          shouldPutInBrackets = true;
        }
      }
    }

    if (shouldPutInBrackets) {
      result += putInBrackets(child->toString());
    } else {
      result += child->toString();
    }

    result += parentOperStr;
  }

  result = result.substr(0, result.length() - parentOperStr.length());

  return result;
}

void IBinaryExpression::validate() const {
  // TODO: implement it
}

}
