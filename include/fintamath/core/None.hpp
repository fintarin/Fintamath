#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class FINTAMATH_EXPORT None {
public:
  static constexpr MathObjectClass getClassStatic() noexcept {
    return nullptr;
  }
};

}
