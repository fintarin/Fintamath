#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Tan : public IFunctionCRTP<INumber, Tan, INumber> {
public:
  Tan() = default;

  std::string toString() const override {
    return "tan";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
