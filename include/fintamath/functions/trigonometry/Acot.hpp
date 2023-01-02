#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acot : public IFunctionCRTP<Acot, INumber> {
public:
  Acot() = default;

  std::string toString() const override {
    return "acot";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
