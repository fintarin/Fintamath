#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acos : public IFunctionCRTP<INumber, Acos, INumber> {
public:
  Acos() = default;

  string toString() const override {
    return "acos";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
