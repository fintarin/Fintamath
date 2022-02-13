#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class ExpressionUtility final {
  public:
    ExpressionUtility() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
