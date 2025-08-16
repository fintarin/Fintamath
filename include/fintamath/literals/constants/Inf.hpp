#pragma once

#include <memory>

#include "fintamath/core/MathObjectClassBody.hpp"
#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {

class Inf : public Constant {
  FINTAMATH_CLASS_BODY(Inf, Constant)

public:
  MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
