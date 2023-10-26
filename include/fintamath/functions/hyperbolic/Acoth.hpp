#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acoth : public IFunctionCRTP<INumber, Acoth, INumber> {
public:
  Acoth() = default;

  std::string toString() const override {
    return "acoth";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acoth;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcothSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acoth, acothExpr);

}
