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

ArgumentsPtrVector IBinaryExpression::getChildren() const {
  return {lhsChild, rhsChild};
}

std::shared_ptr<IMathObject> IBinaryExpression::simplify() {
  simplifyChild(lhsChild);
  simplifyChild(rhsChild);

  if (func->isNonExressionEvaluatable() && func->doArgsMatch({*lhsChild, *rhsChild})) {
    return (*func)(*lhsChild, *rhsChild);
  }

  if (auto res = simplifyChildren()) {
    return res;
  }

  return {};
}

void IBinaryExpression::validate() const {
  if (const auto childExpr = cast<IExpression>(lhsChild)) {
    childExpr->validate();
  }
  if (const auto childExpr = cast<IExpression>(rhsChild)) {
    childExpr->validate();
  }

  validateArgs(*func, {lhsChild, rhsChild});
}

}
