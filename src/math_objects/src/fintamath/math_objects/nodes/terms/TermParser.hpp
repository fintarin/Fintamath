#pragma once

#include "fintamath/math_objects/nodes/terms/Term.hpp"

namespace fintamath {
  class TermParser final {
  public:
    TermParser() = delete;

    static std::unique_ptr<Term> parse(const std::string_view &str);
  };
}
