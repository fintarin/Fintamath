#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class LessEqv final : public IOperatorCRTP<Boolean, LessEqv, IComparable, IComparable> {
public:
  LessEqv() : IOperatorCRTP(IOperator::Priority::Comparison, true) {
  }

  std::string toString() const override {
    return "<=";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::LessEqv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(LessEqv, lessEqvExpr);

}
