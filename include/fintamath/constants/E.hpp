#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public IConstant {
  FINTAMATH_CLASS_BODY(E, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Real::getClassStatic();
  }

  std::shared_ptr<const IMathObject> approximateValue() const noexcept override;
};

}
