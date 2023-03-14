#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Degrees : public IFunctionCRTP<INumber, Degrees, INumber> {
public:
  Degrees() = default;

  string toString() const override {
    return "degrees";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
