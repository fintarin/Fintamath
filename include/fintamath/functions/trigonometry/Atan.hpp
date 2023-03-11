#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atan : public IFunctionCRTP<INumber, Atan, INumber> {
public:
  Atan() = default;

  std::string toString() const override {
    return "atan";
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsVector &argsVect) const override;
};

}
