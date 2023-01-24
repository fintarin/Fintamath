#pragma once

#include "fintamath/literals/Boolean.hpp"
#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False : public IConstantCRTP<False> {
public:
  std::string toString() const override {
    return Boolean(false).toString();
  }

protected:
  MathObjectPtr call() const override;
};

}
