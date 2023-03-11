#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cosh : public IFunctionCRTP<INumber, Cosh, INumber> {
public:
  Cosh() = default;

  std::string toString() const override {
    return "cosh";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
