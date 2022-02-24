#pragma once

#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  class MathObjectParser final {
  public:
    MathObjectParser() = delete;
    static std::string_view deleteOpenAndCloseBracket(const std::string_view &str);
    static std::unique_ptr<MathObject> parse(const std::string_view &str);
  };
}
