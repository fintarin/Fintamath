#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class NodeUtility final {
  public:
    NodeUtility() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
