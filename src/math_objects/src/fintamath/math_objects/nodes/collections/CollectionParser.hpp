#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class CollectionParser final {
  public:
    CollectionParser() = delete;

    static std::unique_ptr<Node> parse(const std::string_view &str);
  };
}
