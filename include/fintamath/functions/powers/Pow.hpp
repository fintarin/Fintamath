#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;
class Complex;

class Pow final : public IOperatorCRTP<INumber, Pow, INumber, INumber> {
public:
  Pow() : IOperatorCRTP(Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "^";
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::Pow;
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override;

private:
  static std::unique_ptr<IMathObject> multiPowSimplify(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Rational &lhs, const Rational &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Real &lhs, const Real &rhs);

  static std::unique_ptr<IMathObject> powSimplify(const Complex &lhs, const Complex &rhs);
};

FINTAMATH_FUNCTION_EXPRESSION(Pow, powExpr);

}
