#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Atanh : public IFunctionCRTP<INumber, Atanh, INumber> {
public:
  Atanh() = default;

  std::string toString() const override {
    return "atanh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Atanh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAtanhSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Atanh, atanhExpr);

}
