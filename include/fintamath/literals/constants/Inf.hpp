#pragma once

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class Inf : public IConstant {
  FINTAMATH_CLASS_BODY(Inf, IConstant)

public:
  MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
