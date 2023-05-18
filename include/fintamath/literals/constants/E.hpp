#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public IConstantCRTP<Real, E> {
public:
  std::string toString() const override {
    return "E";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::E);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
