#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Tan : public IFunctionCRTP<Tan, INumber> {
public:
  Tan() = default;

  std::string toString() const override {
    return "tan";
  }

protected:
  MathObjectPtr call(const ArgumentsVector &argsVect) const override;
};

}
