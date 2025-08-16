#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

// TODO: remove None
struct None {
  static constexpr MathObjectClass getClassStatic() noexcept {
    return nullptr;
  }
};

}
