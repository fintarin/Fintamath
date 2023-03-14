#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sinh : public IFunctionCRTP<INumber, Sinh, INumber> {
public:
  Sinh() = default;

  string toString() const override {
    return "sinh";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
