#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acosh : public IFunctionCRTP<INumber, Acosh, INumber> {
public:
  Acosh() = default;

  string toString() const override {
    return "acosh";
  }

protected:
  unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
