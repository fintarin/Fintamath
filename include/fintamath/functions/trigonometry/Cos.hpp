#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cos : public IFunctionCRTP<INumber, Cos, INumber> {
public:
  Cos() = default;

  std::string toString() const override {
    return "cos";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
