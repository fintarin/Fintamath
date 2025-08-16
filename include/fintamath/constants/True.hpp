#pragma once

#include <memory>

#include "fintamath/constants/Constant.hpp"
#include "fintamath/core/Boolean.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"

namespace fintamath {

class True : public Constant {
  FINTAMATH_CLASS_BODY(True, Constant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
