#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

#include "fintamath/core/IArithmetic.hpp"

namespace fintamath {

class Deg : public IConstantCRTP<IArithmetic, Deg> {
public:
  std::string toString() const override {
    return "Deg";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Deg);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
