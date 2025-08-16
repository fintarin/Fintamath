#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class NegInf : public IConstant {
  FINTAMATH_CLASS_BODY(NegInf, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return INumber::getClassStatic();
  }

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
