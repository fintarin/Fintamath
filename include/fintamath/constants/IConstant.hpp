#pragma once

#include <memory>

#include "fintamath/core/IMathObject.hpp"

namespace fintamath {

class IConstant : public IMathObject {
  FINTAMATH_INTERFACE_BODY(Constant, IMathObject)

public:
  virtual constexpr MathObjectClass getValueClass() const noexcept = 0;

  virtual std::unique_ptr<IMathObject> getValue(bool shouldApproximate) const noexcept = 0;

  std::string toString() const noexcept override;
};

}
