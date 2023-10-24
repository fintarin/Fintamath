#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ceil : public IFunctionCRTP<INumber, Ceil, INumber> {
public:
  Ceil() = default;

  std::string toString() const override {
    return "ceil";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Ceil;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCeilSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Ceil, ceilExpr);

}
