#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class None {
public:
  static constexpr std::nullptr_t getClassStatic() noexcept {
    return nullptr;
  }
};

}
