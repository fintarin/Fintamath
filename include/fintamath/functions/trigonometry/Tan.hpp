#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Tan : public IFunctionCRTP<Tan, INumber> {
public:
  Tan() = default;

  std::string toString() const override {
    return "tan";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
