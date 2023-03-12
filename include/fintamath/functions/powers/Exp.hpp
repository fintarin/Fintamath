#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Exp : public IFunctionCRTP<INumber, Exp, INumber> {
public:
  Exp() = default;

  std::string toString() const override {
    return "exp";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
