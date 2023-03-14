#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lb : public IFunctionCRTP<INumber, Lb, INumber> {
public:
  Lb() = default;

  string toString() const override {
    return "lb";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
