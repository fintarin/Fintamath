#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperator.hpp"

namespace fintamath {
  class BinaryArithmeticOperatorParser final {
  public:
    BinaryArithmeticOperatorParser() = delete;

    static std::unique_ptr<BinaryArithmeticOperator> parse(const std::string_view &str);
  };
}
