#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Cosh : public IFunctionCRTP<INumber, Cosh, INumber> {
public:
  Cosh() = default;

  std::string toString() const override {
    return "cosh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Cosh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCoshSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> coshSimplify(const Real &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Cosh, coshExpr);

}
