#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Mul final : public IOperatorCRTP<IArithmetic, Mul, IArithmetic, IArithmetic> {
public:
  Mul() : IOperatorCRTP(Priority::Multiplication, true) {
  }

  std::string toString() const override {
    return "*";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Mul;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Mul, mulExpr);

}
