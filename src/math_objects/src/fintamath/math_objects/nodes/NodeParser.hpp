#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class NodeParser final {
  public:
    NodeParser() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
