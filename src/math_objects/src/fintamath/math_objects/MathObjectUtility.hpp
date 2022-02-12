#pragma once

#include <string>

#include "fintamath/math_objects/MathObject.hpp"

namespace fintamath {
  class MathObjectUtility final {
  public:
    MathObjectUtility() = delete;

    static MathObjectPtr parse(const std::string_view &str);
  };
}
