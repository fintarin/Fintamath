#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

#include <stdexcept>

using namespace fintamath;

Expression::Expression(const std::string_view & /*str*/) {
  throw std::invalid_argument("Expression invalid input");
}

std::string Expression::toString() const {
  return "expression";
}
