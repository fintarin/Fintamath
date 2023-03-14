#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class Pi : public IConstantCRTP<Real, Pi> {
public:
  string toString() const override {
    return "Pi";
  }

protected:
  unique_ptr<IMathObject> call() const override;
};

}
