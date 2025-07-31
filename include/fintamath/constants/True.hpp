#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Boolean.hpp"
#include "fintamath/core/FintamathClassBody.hpp"

namespace fintamath {

class True : public IConstant {
  FINTAMATH_CLASS_BODY(True, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
