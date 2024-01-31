#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Csch : public IFunctionCRTP<INumber, Csch, INumber> {
public:
  Csch() = default;

  std::string toString() const override {
    return "csch";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Csch;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCschSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Csch, cschExpr);

}
