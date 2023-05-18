#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True : public IConstantCRTP<Boolean, True> {
public:
  std::string toString() const override {
    return Boolean(true).toString();
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::True);
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
