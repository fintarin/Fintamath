#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class Indeterminate : public IConstantCRTP<IMathObject, Indeterminate> {
public:
  std::string toString() const override {
    return "Indeterminate";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Indeterminate);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
