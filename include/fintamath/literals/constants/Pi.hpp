#pragma once

#include <memory>
#include <string>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Pi final : public IConstantCRTP<Real, Pi> {
public:
  std::string toString() const override {
    return "Pi";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Pi;
  }

protected:
  std::unique_ptr<IMathObject> call() const override;
};

}
