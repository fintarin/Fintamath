#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/FintamathClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class FINTAMATH_EXPORT NegInf : public IConstant {
  FINTAMATH_CLASS_BODY(NegInf, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass NegInf::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

}
