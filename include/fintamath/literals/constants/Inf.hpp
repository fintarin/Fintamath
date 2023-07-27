#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Inf : public IConstantCRTP<INumber, Inf> {
public:
  std::string toString() const override {
    return "Inf";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Inf);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
