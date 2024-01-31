#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True final : public IConstantCRTP<Boolean, True> {
public:
  std::string toString() const override {
    return Boolean(true).toString();
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::True;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
