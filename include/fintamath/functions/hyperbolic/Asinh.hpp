#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Asinh final : public IFunctionCRTP<INumber, Asinh, INumber> {
public:
  Asinh() = default;

  std::string toString() const override {
    return "asinh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Asinh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAsinhSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Asinh, asinhExpr);

}
