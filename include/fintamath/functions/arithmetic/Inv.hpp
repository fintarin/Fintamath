#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Inv : public IFunctionCRTP<INumber, Inv, INumber> {
public:
  Inv() = default;

  string toString() const override {
    return "inv";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};
}