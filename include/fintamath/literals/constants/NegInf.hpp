#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class NegInf final : public IConstantCRTP<INumber, NegInf> {
  FINTAMATH_CLASS_BODY(NegInf)

public:
  std::string toString() const override {
    return "-Inf";
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
