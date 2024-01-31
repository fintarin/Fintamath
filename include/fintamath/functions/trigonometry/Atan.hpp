#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Atan : public IFunctionCRTP<INumber, Atan, INumber> {
public:
  Atan() = default;

  std::string toString() const override {
    return "atan";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Atan;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAtanSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Atan, atanExpr);

}
