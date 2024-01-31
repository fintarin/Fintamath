#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Sub final : public IOperatorCRTP<IArithmetic, Sub, IArithmetic, IArithmetic> {
public:
  Sub() : IOperatorCRTP(IOperator::Priority::Addition) {
  }

  std::string toString() const override {
    return "-";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sub;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Sub, subExpr);

}
