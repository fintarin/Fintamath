#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True : public IConstantCRTP<Boolean, True> {
public:
  string toString() const override {
    return Boolean(true).toString();
  }

protected:
  unique_ptr<IMathObject> call() const override;
};

}
