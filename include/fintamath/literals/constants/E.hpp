#pragma once

#include "fintamath/literals/constants/IConstant.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

class E : public IConstantCRTP<Real, E> {
public:
  string toString() const override {
    return "E";
  }

protected:
  unique_ptr<IMathObject> call() const override;
};

}
