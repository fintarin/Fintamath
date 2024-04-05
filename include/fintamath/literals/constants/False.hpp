#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False final : public IConstantCRTP<Boolean, False> {
  FINTAMATH_CLASS_BODY(False)

public:
  std::string toString() const noexcept override {
    return Boolean(false).toString();
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
