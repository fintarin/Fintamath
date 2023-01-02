#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cot : public IFunctionCRTP<Cot, INumber> {
public:
  Cot() = default;

  std::string toString() const override {
    return "cot";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
