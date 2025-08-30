#pragma once

#include <memory>

#include "fintamath/constants/Constant.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/Number.hpp"

namespace fintamath {

class Pi : public Constant {
  FINTAMATH_CLASS_BODY(Pi, Constant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Number::getClassStatic();
  }

  std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
