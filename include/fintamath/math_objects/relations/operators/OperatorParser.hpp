#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/Operator.hpp"
#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

namespace fintamath {
  class OperatorParser final {
  public:
    OperatorParser() = delete;

    static std::unique_ptr<Expression> parse(const std::string_view &str);
  };
}
