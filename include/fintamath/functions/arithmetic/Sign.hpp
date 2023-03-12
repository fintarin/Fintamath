#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sign : public IFunctionCRTP<INumber, Sign, INumber> {
public:
  Sign() = default;

  std::string toString() const override {
    return "sign";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
