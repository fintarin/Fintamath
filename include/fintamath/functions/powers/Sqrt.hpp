#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sqrt : public IFunctionCRTP<INumber, Sqrt, INumber> {
public:
  Sqrt() = default;

  std::string toString() const override {
    return "sqrt";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sqrt;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Sqrt, sqrtExpr);

}
