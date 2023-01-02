#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cos : public IFunctionCRTP<Cos, INumber> {
public:
  Cos() = default;

  std::string toString() const override {
    return "cos";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
