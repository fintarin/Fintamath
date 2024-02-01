#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Not final : public IOperatorCRTP<Boolean, Not, Boolean> {
public:
  Not() : IOperatorCRTP(Priority::PrefixUnary) {
  }

  std::string toString() const override {
    return "~";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Not;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Not, notExpr);

}
