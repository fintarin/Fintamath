#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cosh : public IFunctionCRTP<INumber, Cosh, INumber> {
public:
  Cosh() = default;

  string toString() const override {
    return "cosh";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
