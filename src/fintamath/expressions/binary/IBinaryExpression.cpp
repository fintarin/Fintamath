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
  std::vector<MathObjectPtr> values;
  values.emplace_back(lhsInfo->clone());
  values.emplace_back(rhsInfo->clone());

  return binaryOperatorToString(cast<IOperator>(*getFunction()), values);
}

void IBinaryExpression::validate() const {
  // TODO: implement it
}

}
