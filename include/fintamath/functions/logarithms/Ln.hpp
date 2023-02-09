#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ln : public IFunctionCRTP<INumber, Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
