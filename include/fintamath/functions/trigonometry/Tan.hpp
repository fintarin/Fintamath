#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Tan : public IFunctionCRTP<INumber, Tan, INumber> {
public:
  Tan() = default;

  std::string toString() const override {
    return "tan";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Tan;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiTanSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Tan, tanExpr);

}
