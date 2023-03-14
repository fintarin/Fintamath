#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atanh : public IFunctionCRTP<INumber, Atanh, INumber> {
public:
  Atanh() = default;

  string toString() const override {
    return "atanh";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
