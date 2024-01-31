#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Impl final : public IOperatorCRTP<Boolean, Impl, Boolean, Boolean> {
public:
  Impl() : IOperatorCRTP(IOperator::Priority::Implication, false) {
  }

  std::string toString() const override {
    return "->";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Impl;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Impl, implExpr);

}
