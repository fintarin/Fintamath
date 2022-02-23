#pragma once

#include <string>

#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  class MathObjectParser final {
  public:
    MathObjectParser() = delete;

    static std::unique_ptr<MathObject> parse(const std::string_view &str);
  };
}
