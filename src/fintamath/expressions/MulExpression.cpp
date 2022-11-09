#include "fintamath/expressions/MulExpression.hpp"

namespace fintamath {
  std::string MulExpression::getClassName() const {
    return "MulExpression";
  }

  MulExpression::Element::Element(const Element &rhs) : inverted(rhs.inverted) {
    info = rhs.info->clone();
  }

  MulExpression::Element &MulExpression::Element::operator=(const Element &rhs) {
    if (this != &rhs) {
      info = rhs.info->clone();
      inverted = rhs.inverted;
    }
    return *this;
  }
}
