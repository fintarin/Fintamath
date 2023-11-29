#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sqr : public IFunctionCRTP<INumber, Sqr, INumber> {
public:
  Sqr() = default;

  std::string toString() const override {
    return "sqr";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sqr;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;
};

FINTAMATH_FUNCTION_EXPRESSION(Sqr, sqrExpr);

}
