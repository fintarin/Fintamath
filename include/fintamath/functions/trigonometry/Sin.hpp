#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sin : public IFunctionCRTP<INumber, Sin, INumber> {
public:
  Sin() = default;

  string toString() const override {
    return "sin";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
