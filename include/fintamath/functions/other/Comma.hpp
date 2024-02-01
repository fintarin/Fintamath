#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/functions/IOperator.hpp"

namespace fintamath {

class Comma final : public IOperatorCRTP<IArithmetic, Comma, IMathObject, IMathObject> {
public:
  Comma() : IOperatorCRTP(Priority::Comma, true) {
  }

  std::string toString() const override {
    return ",";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Comma;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Comma, commaExpr);

}
