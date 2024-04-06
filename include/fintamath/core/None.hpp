#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

struct None {
  static constexpr MathObjectClass getClassStatic() {
    return nullptr;
  }
};

}
