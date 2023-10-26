#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Sinh : public IFunctionCRTP<INumber, Sinh, INumber> {
public:
  Sinh() = default;

  std::string toString() const override {
    return "sinh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sinh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSinhSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> sinhSimplify(const Real &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sinh, sinhExpr);

}
