#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Neg : public IOperatorCRTP<IArithmetic, Neg, IArithmetic> {
public:
  Neg() : IOperatorCRTP(IOperator::Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "-";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Neg;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Neg, negExpr);

}
