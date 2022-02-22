#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/ArithmeticOperator.hpp"

namespace fintamath {
  class ArithmeticOperatorParser final {
  public:
    ArithmeticOperatorParser() = delete;

    static std::unique_ptr<ArithmeticOperator> parse(const std::string_view &str);
  };
}
