#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Pi : public IConstantCRTP<Real, Pi> {
public:
  std::string toString() const override {
    return "Pi";
  }

protected:
  MathObjectPtr call() const override;
};

}
