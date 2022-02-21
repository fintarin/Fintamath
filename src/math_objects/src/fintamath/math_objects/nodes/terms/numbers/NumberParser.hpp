#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class NumberParser final {
  public:
    NumberParser() = delete;

    static std::unique_ptr<Node> parse(const std::string_view &str);
  };
}
