#include "fintamath/expressions/AddExpression.hpp"

namespace fintamath {
  std::string AddExpression::getClassName() const {
    return "AddExpression";
  }

  AddExpression::Element::Element(const Element &rhs) : inverted(rhs.inverted) {
    info = rhs.info->clone();
  }

  AddExpression::Element &AddExpression::Element::operator=(const Element &rhs) {
    if (this != &rhs) {
      info = rhs.info->clone();
      inverted = rhs.inverted;
    }
    return *this;
  }
}