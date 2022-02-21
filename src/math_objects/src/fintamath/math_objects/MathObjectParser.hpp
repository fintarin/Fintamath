#pragma once

#include <string>

#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  class MathObjectParser final {
  public:
    MathObjectParser() = delete;

    static MathObjectPtr parse(const std::string_view &str);
  };
}
