#pragma once

#include "fintamath/functions/IFunction.hpp"

namespace fintamath {

class INumber;

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