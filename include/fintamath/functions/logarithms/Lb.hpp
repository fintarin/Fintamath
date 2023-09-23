#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Lb : public IFunctionCRTP<INumber, Lb, INumber> {
public:
  Lb() = default;

  std::string toString() const override {
    return "lb";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Lb;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Lb, lbExpr);

}
