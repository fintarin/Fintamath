#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Cos : public IFunctionCRTP<INumber, Cos, INumber> {
public:
  Cos() = default;

  std::string toString() const override {
    return "cos";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Cos;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCosSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> cosSimplify(const Real &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Cos, cosExpr);

}
