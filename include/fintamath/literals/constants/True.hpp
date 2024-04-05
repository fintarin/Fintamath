#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True final : public IConstantCRTP<Boolean, True> {
  FINTAMATH_CLASS_BODY(True)

public:
  std::string toString() const noexcept override {
    return Boolean(true).toString();
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
