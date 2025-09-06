#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class MathObjectBase {
public:
  virtual ~MathObjectBase() noexcept = default;

  static constexpr MathObjectClass getClassStatic() noexcept {
    return nullptr;
  }

  virtual MathObjectClass getClass() const noexcept;
};

}
