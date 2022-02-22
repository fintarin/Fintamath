#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/unary_arithmetic_operators/UnaryArithmeticOperator.hpp"

namespace fintamath {
  class UnaryArithmeticOperatorParser final {
  public:
    UnaryArithmeticOperatorParser() = delete;

    static std::unique_ptr<UnaryArithmeticOperator> parse(const std::string_view &str);
  };
}
