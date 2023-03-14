#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Abs : public IFunctionCRTP<INumber, Abs, INumber> {
public:
  Abs() = default;

  string toString() const override {
    return "abs";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
