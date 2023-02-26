#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IBinaryExpression &rhs)
    : lhsInfo(rhs.lhsInfo->clone()),
      rhsInfo(rhs.rhsInfo->clone()) {
}

IBinaryExpression::IBinaryExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : lhsInfo(std::move(lhs)),
      rhsInfo(std::move(rhs)) {
}

IBinaryExpression &IBinaryExpression::operator=(const IBinaryExpression &rhs) {
  if (&rhs != this) {
    lhsInfo = rhs.lhsInfo->clone();
    rhsInfo = rhs.rhsInfo->clone();
  }

  return *this;
}

void IBinaryExpression::setPrecision(uint8_t precision) {
  setMathObjectPrecision(lhsInfo, precision);
  setMathObjectPrecision(rhsInfo, precision);
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
