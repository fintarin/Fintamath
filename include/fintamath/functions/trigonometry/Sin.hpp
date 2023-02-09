#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sin : public IFunctionCRTP<INumber, Sin, INumber> {
public:
  Sin() = default;

  std::string toString() const override {
    return "sin";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
