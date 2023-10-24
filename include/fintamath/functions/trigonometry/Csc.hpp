#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Csc : public IFunctionCRTP<INumber, Csc, INumber> {
public:
  Csc() = default;

  std::string toString() const override {
    return "csc";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Csc;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCscSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Csc, cscExpr);

}
