#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Pi final : public IConstantCRTP<Real, Pi> {
  FINTAMATH_CLASS_BODY(Pi)

public:
  std::string toString() const noexcept override {
    return "Pi";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
