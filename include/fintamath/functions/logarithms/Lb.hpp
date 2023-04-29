#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lb : public IFunctionCRTP<INumber, Lb, INumber> {
public:
  Lb() = default;

  std::string toString() const override {
    return "lb";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

}
