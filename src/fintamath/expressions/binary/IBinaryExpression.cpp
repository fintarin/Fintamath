#include "fintamath/expressions/binary/IBinaryExpression.hpp"

#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/ExpressionUtils.hpp"
#include "fintamath/expressions/IExpression.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/meta/Converter.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

IBinaryExpression::IBinaryExpression(const IBinaryExpression &rhs)
    : func(cast<IFunction>(rhs.func->clone())),
      lhsChild(rhs.lhsChild->clone()),
      rhsChild(rhs.rhsChild->clone()) {
}

IBinaryExpression &IBinaryExpression::operator=(const IBinaryExpression &rhs) {
  if (&rhs != this) {
    func = cast<IFunction>(rhs.func->clone());
    lhsChild = rhs.lhsChild->clone();
    rhsChild = rhs.rhsChild->clone();
  }

  return *this;
}

IBinaryExpression::IBinaryExpression(const IFunction &func, std::shared_ptr<IMathObject> lhsChild,
                                     std::shared_ptr<IMathObject> rhsChild)
    : func(cast<IFunction>(func.clone())),
      lhsChild(std::move(lhsChild)),
      rhsChild(std::move(rhsChild)) {
  compress();
}

void IBinaryExpression::setPrecision(uint8_t precision) {
  setMathObjectPrecision(lhsChild, precision);
  setMathObjectPrecision(rhsChild, precision);
}

std::string IBinaryExpression::toString() const {
  ArgumentsPtrVector values;
  values.emplace_back(lhsChild);
  values.emplace_back(rhsChild);
  return binaryOperatorToString(*cast<IOperator>(getFunction()), values);
}

std::shared_ptr<IFunction> IBinaryExpression::getFunction() const {
  return func;
}

std::shared_ptr<IMathObject> IBinaryExpression::simplify() {
  simplifyExpr(lhsChild);
  simplifyExpr(rhsChild);

  if (auto res = simplifyChildren()) {
    return res;
  }

  return shared_from_this();
}

void IBinaryExpression::validate() const {
  validateArgs(*func, {lhsChild, rhsChild});
}

void IBinaryExpression::compress() {
  if (auto expr = cast<Expression>(lhsChild)) {
    lhsChild = expr->getChild();
  }
  if (auto expr = cast<Expression>(rhsChild)) {
    rhsChild = expr->getChild();
  }
}

}
