#pragma once

#include <memory>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/Constant.hpp"

namespace fintamath {

class NegInf : public Constant {
  FINTAMATH_CLASS_BODY(NegInf, Constant)

public:
  MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
