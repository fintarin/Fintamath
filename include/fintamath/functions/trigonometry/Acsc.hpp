#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acsc final : public IFunctionCRTP<INumber, Acsc, INumber> {
public:
  Acsc() = default;

  std::string toString() const override {
    return "acsc";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acsc;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcscSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acsc, acscExpr);

}
