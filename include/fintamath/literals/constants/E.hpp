#pragma once

#include "fintamath/literals/constants/IConstant.hpp"

namespace fintamath {

class E : public IConstantCRTP<E> {
public:
  std::string toString() const override {
    return "E";
  }

protected:
  MathObjectPtr call() const override;
};

}
