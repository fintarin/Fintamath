#pragma once

#include <string>

#include "fintamath/math_objects/relations/operators/Operator.hpp"

namespace fintamath {
  class OperatorParser final {
  public:
    OperatorParser() = delete;

    static std::unique_ptr<Operator> parse(const std::string_view &str);
  };
}
