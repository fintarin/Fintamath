#pragma once

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  class ExpressionParser final {
  public:
    ExpressionParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);
  };
}
