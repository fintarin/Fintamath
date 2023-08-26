#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Complex.hpp"

namespace fintamath {

class I : public IConstantCRTP<Complex, I> {
public:
  std::string toString() const override {
    return "I";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::I);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
