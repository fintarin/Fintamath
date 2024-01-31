#pragma once

#include "fintamath/core/IComparable.hpp"
#include "fintamath/functions/IOperator.hpp"
#include "fintamath/literals/Variable.hpp"

namespace fintamath {

class Integral : public IFunctionCRTP<IComparable, Integral, IComparable, Variable> {
public:
  Integral() : IFunctionCRTP(false) {
  }

  std::string toString() const override {
    return "integral";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Integral;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Integral, integralExpr);

}
