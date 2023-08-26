#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Acot : public IFunctionCRTP<INumber, Acot, INumber> {
public:
  Acot() = default;

  std::string toString() const override {
    return "acot";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Acot);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcotSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acot, acotExpr);

}
