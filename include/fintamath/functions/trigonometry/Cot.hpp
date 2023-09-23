#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Cot : public IFunctionCRTP<INumber, Cot, INumber> {
public:
  Cot() = default;

  std::string toString() const override {
    return "cot";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Cot;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiCotSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Cot, cotExpr);

}
