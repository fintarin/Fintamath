#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Acosh final : public IFunctionCRTP<INumber, Acosh, INumber> {
public:
  Acosh() = default;

  std::string toString() const override {
    return "acosh";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Acosh;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAcoshSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Acosh, acoshExpr);

}
