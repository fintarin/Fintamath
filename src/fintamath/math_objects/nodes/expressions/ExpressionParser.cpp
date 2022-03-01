#include "fintamath/math_objects/nodes/expressions/ExpressionParser.hpp"

#include <stdexcept>

#include "fintamath/math_objects/ParserInjector.hpp"

namespace fintamath {
  std::unique_ptr<Expression> ExpressionParser::parse(const std::string_view &str) {
    INJECT_CONSTRUCTOR(Expression, str)
    return nullptr;
  }
}