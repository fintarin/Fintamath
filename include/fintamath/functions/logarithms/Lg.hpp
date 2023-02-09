#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lg : public IFunctionCRTP<INumber, Lg, INumber> {
public:
  Lg() = default;

  std::string toString() const override {
    return "lg";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
