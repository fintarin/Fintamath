#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acot final : public IFunctionCRTP<INumber, Acot, INumber> {
public:
  Acot() = default;

  std::string toString() const override {
    return "acot";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acot;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcotSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acot, acotExpr);

}
