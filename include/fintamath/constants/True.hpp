#pragma once

#include <memory>

#include "fintamath/constants/IConstant.hpp"
#include "fintamath/core/Boolean.hpp"
#include "fintamath/core/MathObjectClassBody.hpp"

namespace fintamath {

class True : public IConstant {
  FINTAMATH_CLASS_BODY(True, IConstant)

public:
  constexpr MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

constexpr MathObjectClass True::getValueClass() const noexcept {
  return Boolean::getClassStatic();
}

}
