#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

using namespace fintamath;

NodePtr ExpressionParser::parse(const std::string_view &str) {
  try {
    return std::make_shared<Expression>(str);
  } catch (const std::invalid_argument &) {
    // do nothing
  }

  return nullptr;
}
