#include "fintamath/expressions/binary/IBinaryExpression.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IBinaryExpression &rhs)
    : function(cast<IFunction>(rhs.function->clone())),
      lhsChild(rhs.lhsChild->clone()),
      rhsChild(rhs.rhsChild->clone()) {
}

IBinaryExpression::IBinaryExpression(MathObjectPtr &&lhs, MathObjectPtr &&rhs)
    : lhsChild(std::move(lhs)),
      rhsChild(std::move(rhs)) {
}

IBinaryExpression &IBinaryExpression::operator=(const IBinaryExpression &rhs) {
  if (&rhs != this) {
    function = cast<IFunction>(rhs.function->clone());
    lhsChild = rhs.lhsChild->clone();
    rhsChild = rhs.rhsChild->clone();
  }

  return *this;
}

void IBinaryExpression::setPrecision(uint8_t precision) {
  setMathObjectPrecision(lhsChild, precision);
  setMathObjectPrecision(rhsChild, precision);
}

std::string IBinaryExpression::toString() const {
  std::vector<MathObjectPtr> values;
  values.emplace_back(lhsChild->clone());
  values.emplace_back(rhsChild->clone());

  return binaryOperatorToString(cast<IOperator>(*getFunction()), values);
}

void IBinaryExpression::validate() const {
  // TODO: implement it
}

const IFunction *IBinaryExpression::getFunction() const {
  return function.get();
}

}
