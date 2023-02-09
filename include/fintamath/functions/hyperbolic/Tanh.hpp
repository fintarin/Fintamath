#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Tanh : public IFunctionCRTP<INumber, Tanh, INumber> {
public:
  Tanh() = default;

  std::string toString() const override {
    return "tanh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
