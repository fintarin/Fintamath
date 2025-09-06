#pragma once

#include <memory>

#include "fintamath/core/MathObject.hpp"

namespace fintamath {

class Constant : public MathObject {
  FINTAMATH_INTERFACE_BODY(Constant, MathObject)

public:
  virtual constexpr MathObjectClass getValueClass() const noexcept = 0;

  virtual std::unique_ptr<MathObject> getValue(bool shouldApproximate) const noexcept = 0;

  std::string toString() const noexcept override;
};

}
