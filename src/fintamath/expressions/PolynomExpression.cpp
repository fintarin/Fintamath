#include "fintamath/expressions/PolynomExpression.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

fintamath::PolynomElement::PolynomElement(const PolynomElement &rhs) : info(rhs.info->clone()), inverted(rhs.inverted) {
}

PolynomElement &PolynomElement::operator=(const PolynomElement &rhs) {
  if (this != &rhs) {
    info = rhs.info->clone();
    inverted = rhs.inverted;
  }

  return *this;
}

PolynomElement::PolynomElement(const MathObjectPtr &info, bool inverted) : PolynomElement(info->clone(), inverted) {
}

PolynomElement::PolynomElement(MathObjectPtr &&info, bool inverted) : info(std::move(info)), inverted(inverted) {
}

void PolynomElement::setPrecision(uint8_t precision) {
  if (is<IExpression>(info)) {
    auto expr = cast<IExpression>(std::move(info));
    expr->setPrecision(precision);
    info = std::move(expr);
    return;
  }

  if (is<INumber>(info)) {
    info = convert<Real>(*info).precise(precision).clone();
  }

  if (is<IConstant>(info)) {
    auto constVal = (*cast<IConstant>(std::move(info)))();

    if (is<INumber>(constVal)) {
      info = convert<Real>(*constVal).precise(precision).clone();
    } else {
      info = std::move(constVal);
    }

    return;
  }
}

}
