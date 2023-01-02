#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acos : public IFunctionCRTP<Acos, INumber> {
public:
  Acos() = default;

  std::string toString() const override {
    return "acos";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
