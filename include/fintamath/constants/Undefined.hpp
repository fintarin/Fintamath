#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Undefined : public IConstant {
  FINTAMATH_CLASS_BODY(Undefined, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass Undefined::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

}
