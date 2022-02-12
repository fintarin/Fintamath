#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class CollectionUtility final {
  public:
    CollectionUtility() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
