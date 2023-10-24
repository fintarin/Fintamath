#pragma once

#include "fintamath/functions/IFunction.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Real;

class Asec : public IFunctionCRTP<INumber, Asec, INumber> {
public:
  Asec() = default;

  std::string toString() const override {
    return "asec";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Asec;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiAsecSimplify(const INumber &rhs);

  static std::unique_ptr<IMathObject> asecSimplify(const Real &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Asec, asecExpr);

}
