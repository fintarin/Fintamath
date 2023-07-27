#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class Undefined : public IConstantCRTP<IMathObject, Undefined> {
public:
  std::string toString() const override {
    return "Undefined";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Undefined);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
