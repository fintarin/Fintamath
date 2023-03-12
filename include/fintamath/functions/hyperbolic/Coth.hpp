#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Coth : public IFunctionCRTP<INumber, Coth, INumber> {
public:
  Coth() = default;

  std::string toString() const override {
    return "coth";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
