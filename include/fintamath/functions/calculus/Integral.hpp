#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Integral : public IFunctionCRTP<IComparable, Integral, IComparable, IComparable> {
public:
  Integral() : IFunctionCRTP(false) {
  }

  std::string toString() const override {
    return "integral";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Integral);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Integral, integralExpr);

}
