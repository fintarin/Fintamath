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
  if (info->instanceOf<IExpression>()) {
    auto expr = cast<IExpression>(std::move(info));
    expr->setPrecision(precision);
    info = std::move(expr);
    return;
  }

  if (info->instanceOf<INumber>()) {
    info = Converter::convert<Real>(*info).precise(precision).clone();
  }

  if (info->instanceOf<IConstant>()) {
    auto constVal = (*cast<IConstant>(std::move(info)))();

    if (auto num = cast<INumber>(std::move(constVal))) {
      info = Converter::convert<Real>(*num).precise(precision).clone();
    } else {
      info = std::move(constVal);
    }

    return;
  }
}

}
