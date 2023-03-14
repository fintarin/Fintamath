#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lg : public IFunctionCRTP<INumber, Lg, INumber> {
public:
  Lg() = default;

  string toString() const override {
    return "lg";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
