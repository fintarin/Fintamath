#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class ComplexInf final : public IConstantCRTP<INumber, ComplexInf> {
  FINTAMATH_CLASS_BODY(ComplexInf)

public:
  std::string toString() const override {
    return "ComplexInf";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
