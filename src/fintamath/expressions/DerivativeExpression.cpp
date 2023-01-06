#include "fintamath/expressions/DerivativeExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

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

uint16_t DerivativeExpression::getBaseOperatorPriority() const {
  return uint16_t(IOperator::Priority::PostfixUnary);
}

void DerivativeExpression::setPrecision(uint8_t precision) {
  if (info->instanceOf<IExpression>()) {
    info->to<IExpression>().setPrecision(precision);
  }
}

MathObjectPtr DerivativeExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr DerivativeExpression::simplify(bool isPrecise) const {
  MathObjectPtr value;
  if (info->instanceOf<IExpression>()) {
    value = info->to<IExpression>().simplify(isPrecise);
  } else {
    value = info->simplify();
  }

  if (value->is<Boolean>()) {
    throw InvalidInputUnaryOpearatorException("'", value->toString(),
                                              InvalidInputUnaryOpearatorException::Type::Postfix);
  }
  if (!isPrecise && value->instanceOf<IExpression>()) {
    return std::make_unique<DerivativeExpression>(*(value->to<IExpression>().simplify(isPrecise)));
  }
  if (value->instanceOf<INumber>() || value->instanceOf<IConstant>()) {
    return std::make_unique<Integer>(0);
  }
  if (value->is<Variable>()) {
    return std::make_unique<Integer>(1);
  }

  return clone();
}

}
