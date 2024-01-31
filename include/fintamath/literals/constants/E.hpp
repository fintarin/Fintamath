#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E final : public IConstantCRTP<Real, E> {
public:
  std::string toString() const override {
    return "E";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::E;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
