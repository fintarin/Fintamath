#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Inf : public IConstant {
  FINTAMATH_CLASS_BODY(Inf, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return INumber::getClassStatic();
  }
};

}
