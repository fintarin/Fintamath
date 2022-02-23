#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Number.hpp"

namespace fintamath {
  class NumberParser final {
  public:
    NumberParser() = delete;

    static std::unique_ptr<Number> parse(const std::string_view &str);
  };
}
