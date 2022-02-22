#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperator.hpp"
#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  class UnaryArithmeticOperatorParser final {
  public:
    UnaryArithmeticOperatorParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);
  };
}
