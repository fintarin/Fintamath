#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public IConstantCRTP<Real, E> {
  FINTAMATH_CLASS_BODY(E, IConstant)

public:
  std::string toString() const override {
    return "E";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
