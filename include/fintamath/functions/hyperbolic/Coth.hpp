#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Coth : public IFunctionCRTP<INumber, Coth, INumber> {
public:
  Coth() = default;

  std::string toString() const override {
    return "coth";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Coth;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCothSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Coth, cothExpr);

}
