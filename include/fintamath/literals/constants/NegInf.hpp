#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class NegInf : public IConstantCRTP<INumber, NegInf> {
public:
  std::string toString() const override {
    return "-Inf";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::NegInf);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
