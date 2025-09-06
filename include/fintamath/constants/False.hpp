#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Boolean.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"

namespace fintamath {

class False : public IConstant {
  FINTAMATH_CLASS_BODY(False, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
