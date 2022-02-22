#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperator.hpp"
#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  class ArithmeticOperatorParser final {
  public:
    ArithmeticOperatorParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);
  };
}
