#pragma once

#include "fintamath/math_objects/nodes/Node.hpp"

namespace fintamath {
  class TermUtility final {
  public:
    TermUtility() = delete;

    static NodePtr parse(const std::string_view &str);
  };
}
