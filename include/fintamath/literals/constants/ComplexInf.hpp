#pragma once

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class ComplexInf : public IConstant {
  FINTAMATH_CLASS_BODY(ComplexInf, IConstant)

public:
  MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
