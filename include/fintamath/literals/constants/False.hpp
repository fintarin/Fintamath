#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class False : public IConstantCRTP<False> {
public:
  std::string toString() const override {
    return "false";
  }

protected:
  MathObjectPtr call() const override;
};

}
