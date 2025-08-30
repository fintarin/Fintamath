#pragma once

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class ComplexInf : public IConstant {
  FINTAMATH_CLASS_BODY(ComplexInf, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass ComplexInf::getValueClass() const noexcept {
  return INumber::getClassStatic();
}

}
