#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class None {
public:
  static constexpr MathObjectClass getClassStatic() noexcept {
    return nullptr;
  }
};

}
