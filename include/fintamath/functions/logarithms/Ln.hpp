#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Ln final : public IFunctionCRTP<INumber, Ln, INumber> {
public:
  Ln() = default;

  std::string toString() const override {
    return "ln";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Ln;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiLnSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Ln, lnExpr);

}
