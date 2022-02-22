#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"

#include <stdexcept>

namespace fintamath {
  std::unique_ptr<Expression> ExpressionParser::parse(const std::string_view &str) {
    try {
      return std::make_unique<Expression>(str);
    } catch (const std::invalid_argument &) {
      // do nothing
    }

    return nullptr;
  }
}