#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  std::unique_ptr<Node> ExpressionParser::parse(const std::string_view &str) {
    try {
      return std::make_unique<Expression>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }

    return nullptr;
  }
}