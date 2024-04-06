#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

class I : public IConstantCRTP<Complex, I> {
  FINTAMATH_CLASS_BODY(I, IConstant)

public:
  std::string toString() const override {
    return "I";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
