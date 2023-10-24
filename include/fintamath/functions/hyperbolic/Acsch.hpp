#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acsch : public IFunctionCRTP<INumber, Acsch, INumber> {
public:
  Acsch() = default;

  std::string toString() const override {
    return "acsch";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acsch;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcschSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acsch, acschExpr);

}
