#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Pi : public IConstant {
  FINTAMATH_CLASS_BODY(Pi, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return INumber::getClassStatic();
  }

  std::shared_ptr<const IMathObject> approximateValue() const noexcept override;
};

}
