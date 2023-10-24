#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Sech : public IFunctionCRTP<INumber, Sech, INumber> {
public:
  Sech() = default;

  std::string toString() const override {
    return "sech";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Sech;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiSechSimplify(const INumber &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Sech, sechExpr);

}
