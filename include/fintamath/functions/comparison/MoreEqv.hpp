#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class MoreEqv : public IOperatorCRTP<Boolean, MoreEqv, IComparable, IComparable> {
public:
  MoreEqv() : IOperatorCRTP(IOperator::Priority::Comparison, true) {
  }

  std::string toString() const override {
    return ">=";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::MoreEqv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(MoreEqv, moreEqvExpr);

}
