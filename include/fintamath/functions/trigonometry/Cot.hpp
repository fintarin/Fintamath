#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cot : public IFunctionCRTP<INumber, Cot, INumber> {
public:
  Cot() = default;

  string toString() const override {
    return "cot";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
