#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lb : public IFunctionCRTP<Lb, INumber> {
public:
  Lb() = default;

  std::string toString() const override {
    return "lb";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
