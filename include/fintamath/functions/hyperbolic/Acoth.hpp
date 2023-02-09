#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acoth : public IFunctionCRTP<INumber, Acoth, INumber> {
public:
  Acoth() = default;

  std::string toString() const override {
    return "acoth";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
