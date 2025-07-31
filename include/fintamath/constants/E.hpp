#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public IConstant {
  FINTAMATH_CLASS_BODY(E, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass E::getValueClass() const noexcept {
  return Real::getClassStatic();
}

}
