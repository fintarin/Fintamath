#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Asech final : public IFunctionCRTP<INumber, Asech, INumber> {
public:
  Asech() = default;

  std::string toString() const override {
    return "asech";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Asech;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAsechSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Asech, asechExpr);

}
