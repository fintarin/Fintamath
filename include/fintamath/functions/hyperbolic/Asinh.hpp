#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Asinh : public IFunctionCRTP<INumber, Asinh, INumber> {
public:
  Asinh() = default;

  std::string toString() const override {
    return "asinh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
