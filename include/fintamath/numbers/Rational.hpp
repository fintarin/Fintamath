#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {

class Rational : public INumberCRTP<Rational> {
public:
  Rational() = default;

  explicit Rational(const std::string &str);

  explicit Rational(Integer inNumer, Integer inDenom);

  Rational(Integer rhs);

  Rational(int64_t rhs);

  std::string toString() const override;

  std::unique_ptr<IMathObject> toMinimalObject() const override;

  int sign() const;

  const Integer &numerator() const;

  const Integer &denominator() const;

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::Rational);
  }

protected:
  bool equals(const Rational &rhs) const override;

  std::strong_ordering compare(const Rational &rhs) const override;

  Rational &add(const Rational &rhs) override;

  Rational &substract(const Rational &rhs) override;

  Rational &multiply(const Rational &rhs) override;

  Rational &divide(const Rational &rhs) override;

  Rational &negate() override;

private:
  void toIrreducibleRational();

  static void toCommonDenominators(Rational &lhs, Rational &rhs);

  Integer numer = 0;
  Integer denom = 1;
};

}
