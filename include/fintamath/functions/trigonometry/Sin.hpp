#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Sin : public IFunctionCRTP<INumber, Sin, INumber> {
public:
  Sin() = default;

  std::string toString() const override {
    return "sin";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sin;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSinSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sin, sinExpr);

}
