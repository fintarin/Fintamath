#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Undefined : public IConstant {
  FINTAMATH_CLASS_BODY(Undefined, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return INumber::getClassStatic();
  }
};

}
