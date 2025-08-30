#pragma once

#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class MathObjectBase {
protected:
  MathObjectBase() = default;

public:
  virtual ~MathObjectBase() noexcept = default;

  static constexpr MathObjectClass getClassStatic() noexcept {
    return nullptr;
  }

  virtual MathObjectClass getClass() const noexcept;

  virtual const MathObjectBase &getDefaultObject() const;
};

}
