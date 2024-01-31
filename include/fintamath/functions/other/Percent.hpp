#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Percent final : public IOperatorCRTP<INumber, Percent, INumber> {
public:
  Percent() : IOperatorCRTP(IOperator::Priority::PostfixUnary) {
  }

  std::string toString() const override {
    return "%";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Percent;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Percent, percentExpr);

}
