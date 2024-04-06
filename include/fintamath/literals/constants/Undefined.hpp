#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class Undefined : public IConstantCRTP<IArithmetic, Undefined> {
  FINTAMATH_CLASS_BODY(Undefined, IConstant)

public:
  std::string toString() const override {
    return "Undefined";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
