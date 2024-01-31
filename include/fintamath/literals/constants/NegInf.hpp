#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class NegInf final : public IConstantCRTP<INumber, NegInf> {
public:
  std::string toString() const override {
    return "-Inf";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::NegInf;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
