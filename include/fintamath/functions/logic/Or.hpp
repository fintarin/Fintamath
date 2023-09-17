#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Or : public IOperatorCRTP<Boolean, Or, Boolean, Boolean> {
public:
  Or() : IOperatorCRTP(IOperator::Priority::Disjunction, true) {
  }

  std::string toString() const override {
    return "|";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Or);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Or, orExpr);

}
