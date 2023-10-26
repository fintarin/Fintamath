#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Sec : public IFunctionCRTP<INumber, Sec, INumber> {
public:
  Sec() = default;

  std::string toString() const override {
    return "sec";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sec;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSecSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sec, secExpr);

}
