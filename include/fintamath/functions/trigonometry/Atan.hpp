#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atan : public IFunctionCRTP<INumber, Atan, INumber> {
public:
  Atan() = default;

  string toString() const override {
    return "atan";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
