#include "fintamath/expressions/unary/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/expressions/Expression.hpp"
#include "fintamath/expressions/unary/IUnaryExpression.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/functions/calculus/Derivative.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"

namespace fintamath {

const Derivative DER;

DerivativeExpression::DerivativeExpression(MathObjectPtr &&obj) : IUnaryExpression(std::move(obj)) {
  function = cast<IFunction>(DER.clone());
}

MathObjectPtr DerivativeExpression::simplify(bool isPrecise) const {
  MathObjectPtr value;

  if (const auto *expr = cast<IExpression>(child.get())) {
    value = expr->simplify(isPrecise);
  } else {
    value = child->toMinimalObject();
  }

  if (is<IExpression>(value)) {
    // TODO: implement derivative of expression
    return std::make_unique<DerivativeExpression>(std::move(value));
  }
  if (is<INumber>(value) || is<IConstant>(value)) {
    return ZERO.clone();
  }
  if (is<Variable>(value)) {
    return ONE.clone();
  }

  return clone();
}

// void DerivativeExpression::validate() const {
//   if (const auto *childExpr = cast<IExpression>(info.get())) {
//     childExpr->validate();
//   }

//   this->validateArgs(*getFunction(), {*info});
// }

void DerivativeExpression::compress() {
  if (auto *childExpr = cast<Expression>(child.get())) {
    child = std::move(childExpr->getInfo());
  }
}

IMathObject *DerivativeExpression::simplify() {
  simplifyExpr(child);

  if (is<IExpression>(child)) {
    // TODO: implement derivative of expression
    return this;
  }

  if (is<INumber>(child) || is<IConstant>(child)) {
    return ZERO.clone().release();
  }
  if (is<Variable>(child)) {
    return ONE.clone().release();
  }

  return this;
}

}
