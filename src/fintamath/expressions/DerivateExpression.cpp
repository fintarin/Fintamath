#include "fintamath/expressions/DerivateExpression.hpp"

#include "fintamath/exceptions/InvalidInputUnaryOpearatorException.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

DerivateExpression::DerivateExpression(const DerivateExpression &rhs) : info(rhs.info->clone()) {
}

DerivateExpression &DerivateExpression::operator=(const DerivateExpression &rhs) {
  if (this == &rhs) {
    return *this;
  }

  info = rhs.info->clone();

  return *this;
}

DerivateExpression::DerivateExpression(const IMathObject &obj) {
  info = obj.simplify();
}

std::string DerivateExpression::toString() const {
  return "(" + info->toString() + ")'";
}

uint16_t DerivateExpression::getBaseOperatorPriority() const {
  return uint16_t(IOperator::Priority::PostfixUnary);
}

void DerivateExpression::setPrecision(uint8_t precision) {
  if (info->instanceOf<IExpression>()) {
    info->to<IExpression>().setPrecision(precision);
  }
}

MathObjectPtr DerivateExpression::simplify() const {
  return simplify(true);
}

MathObjectPtr DerivateExpression::simplify(bool isPrecise) const {
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
    return std::make_unique<DerivateExpression>(*(value->to<IExpression>().simplify(isPrecise)));
  }
  if (value->instanceOf<INumber>() || value->is<IConstant>()) {
    return std::make_unique<Integer>(0);
  }
  if (value->is<Variable>()) {
    return std::make_unique<Integer>(1);
  }

  return clone();
}

}
