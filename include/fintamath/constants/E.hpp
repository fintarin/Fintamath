#pragma once

#include <memory>

#include "fintamath/constants/Constant.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public Constant {
  FINTAMATH_CLASS_BODY(E, Constant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Real::getClassStatic();
  }

  std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
