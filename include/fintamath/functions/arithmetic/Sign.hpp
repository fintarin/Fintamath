#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

class Sign : public IFunctionCRTP<Sign, INumber> {
public:
  Sign() = default;

  std::string toString() const override {
    return "sign";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
