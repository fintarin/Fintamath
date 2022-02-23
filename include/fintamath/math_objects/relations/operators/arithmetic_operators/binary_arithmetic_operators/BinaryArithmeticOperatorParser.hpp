#pragma once

#include <string>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"
#include "fintamath/math_objects/relations/operators/arithmetic_operators/binary_arithmetic_operators/BinaryArithmeticOperator.hpp"

namespace fintamath {
  class BinaryArithmeticOperatorParser final {
  public:
    BinaryArithmeticOperatorParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);

  private:
    static void ignoreBrackets(const std::string_view &str, int &position);
    static std::unique_ptr<Expression> createExpression(const std::string_view &str, int splitPosition, const std::shared_ptr<Relation>& relation);
  };
}
