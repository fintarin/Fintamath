#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Add : public IOperatorCRTP<IArithmetic, Add, IArithmetic, IArithmetic> {
public:
  Add() : IOperatorCRTP(IOperator::Priority::Addition, true) {
  }

  std::string toString() const override {
    return "+";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Add);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Add, addExpr);

}
