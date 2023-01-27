#include "fintamath/expressions/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
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

DerivativeExpression::DerivativeExpression(const DerivativeExpression &rhs) : info(rhs.info->clone()) {
}

DerivativeExpression &DerivativeExpression::operator=(const DerivativeExpression &rhs) {
  if (this == &rhs) {
    return *this;
  }

  info = rhs.info->clone();

  return *this;
}

DerivativeExpression::DerivativeExpression(const IMathObject &obj) {
  info = obj.simplify();
}

std::string DerivativeExpression::toString() const {
  return "(" + info->toString() + ")'";
}

const IFunction *DerivativeExpression::getFunction() const {
  return &DER;
}

void DerivativeExpression::setPrecision(uint8_t precision) {
  if (auto *expr = cast<IExpression>(info.get())) {
    expr->setPrecision(precision);
  }
}

MathObjectPtr DerivativeExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr DerivativeExpression::simplify(bool isPrecise) const {
  MathObjectPtr value;

  if (const auto *expr = cast<IExpression>(info.get())) {
    value = expr->simplify(isPrecise);
  } else {
    value = info->simplify();
  }

  if (cast<Boolean>(value.get())) {
    throw InvalidInputUnaryOpearatorException("'", value->toString(),
                                              InvalidInputUnaryOpearatorException::Type::Postfix);
  }
  if (auto *expr = cast<IExpression>(value.get()); expr && !isPrecise) {
    return std::make_unique<DerivativeExpression>(*(expr->simplify(isPrecise)));
  }
  if (cast<INumber>(value.get()) || cast<IConstant>(value.get())) {
    return ZERO.clone();
  }
  if (cast<Variable>(value.get())) {
    return ONE.clone();
  }

  return clone();
}

}
