#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Tanh : public IFunctionCRTP<INumber, Tanh, INumber> {
public:
  Tanh() = default;

  string toString() const override {
    return "tanh";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
