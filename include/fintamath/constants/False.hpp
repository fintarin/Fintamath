#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/ClassBody.hpp"
#include "fintamath/variables/Boolean.hpp"

namespace fintamath {

class False : public IConstant {
  FINTAMATH_CLASS_BODY(False, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override {
    return Boolean::getClassStatic();
  }

  std::shared_ptr<const IMathObject> getValue() const noexcept override;
};

}
