#pragma once

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

class ImaginaryUnit : public IConstant {
  FINTAMATH_CLASS_BODY(ImaginaryUnit, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Complex::getClassStatic();
  }

  SharedPtr<IMathObject> getValue() const noexcept override;

  std::string toString() const noexcept override;
};

}
