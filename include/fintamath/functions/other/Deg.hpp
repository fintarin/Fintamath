#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Deg : public IOperatorCRTP<INumber, Deg, INumber> {
public:
  Deg() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "deg";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Deg;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Deg, degExpr);

}
