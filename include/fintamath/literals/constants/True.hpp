#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class True : public IConstantCRTP<True> {
public:
  std::string toString() const override {
    return "true";
  }

protected:
  MathObjectPtr call() const override;
};

}
