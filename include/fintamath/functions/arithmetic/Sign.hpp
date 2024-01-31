#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sign : public IFunctionCRTP<INumber, Sign, INumber> {
public:
  Sign() = default;

  std::string toString() const override {
    return "sign";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sign;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSignSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sign, signExpr);

}
