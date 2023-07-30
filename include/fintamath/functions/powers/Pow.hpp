#pragma once

#include "fintamath/functions/IOperator.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class Integer;
class Rational;
class Real;

class Pow : public IOperatorCRTP<INumber, Pow, INumber, INumber> {
public:
  Pow() : IOperatorCRTP(IOperator::Priority::Exponentiation, false) {
  }

  std::string toString() const override {
    return "^";
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Pow);
  }

protected:
  std::unique_ptr<IMathObject> call(const ArgumentsRefVector &argsVect) const override;

private:
  static std::unique_ptr<IMathObject> multiPowSimpl(const INumber &lhs, const INumber &rhs);

  static std::unique_ptr<IMathObject> powSimpl(const Integer &lhs, const Integer &rhs);

  static std::unique_ptr<IMathObject> powSimpl(const Rational &lhs, const Rational &rhs);

  static std::unique_ptr<IMathObject> powSimpl(const Real &lhs, const Real &rhs);
};

}
