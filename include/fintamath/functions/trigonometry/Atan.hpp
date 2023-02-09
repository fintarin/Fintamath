#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atan : public IFunctionCRTP<INumber, Atan, INumber> {
public:
  Atan() = default;

  std::string toString() const override {
    return "atan";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
