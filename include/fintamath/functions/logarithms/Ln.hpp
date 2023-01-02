#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ln : public IFunctionCRTP<Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
