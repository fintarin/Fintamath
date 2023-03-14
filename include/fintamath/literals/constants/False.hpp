#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False : public IConstantCRTP<Boolean, False> {
public:
  string toString() const override {
    return Boolean(false).toString();
  }

protected:
  unique_ptr<IMathObject> call() const override;
};

}
