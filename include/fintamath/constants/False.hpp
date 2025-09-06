#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Boolean.hpp"
#include "fintamath/core/FintamathClassBody.hpp"

namespace fintamath {

class FINTAMATH_EXPORT False : public IConstant {
  FINTAMATH_CLASS_BODY(False, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass False::getValueClass() const noexcept {
  return Boolean::getClassStatic();
}

}
