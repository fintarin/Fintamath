#pragma once

#include <memory>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True : public IConstant {
  FINTAMATH_CHILD_CLASS_BODY(True, IConstant)

public:
  MathObjectClass getValueClass() const noexcept override;

  std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept override;
};

}
