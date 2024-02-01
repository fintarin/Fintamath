#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Boolean.hpp"

namespace fintamath {

class Nequiv final : public IOperatorCRTP<Boolean, Nequiv, Boolean, Boolean> {
public:
  Nequiv() : IOperatorCRTP(Priority::Equivalence, true) {
  }

  std::string toString() const override {
    return "!<->";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Nequiv;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Nequiv, nequivExpr);

}
