#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sinh : public IFunctionCRTP<INumber, Sinh, INumber> {
public:
  Sinh() = default;

  std::string toString() const override {
    return "sinh";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
