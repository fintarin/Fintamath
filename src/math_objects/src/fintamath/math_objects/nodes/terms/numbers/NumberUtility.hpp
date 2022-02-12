#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class NumberUtility final {
  public:
    NumberUtility() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
