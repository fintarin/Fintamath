#pragma once

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/variables/Boolean.hpp"

namespace fintamath {

class True : public IConstant {
  FINTAMATH_CLASS_BODY(True, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::unique_ptr<IMathObject> toMinimalObject() const noexcept override;
};

}
