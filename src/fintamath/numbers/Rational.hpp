#pragma once

#include "fintamath/numbers/Integer.hpp"

namespace fintamath {
  class Rational : public Number<Rational> {
  public:
    Rational() = default;

    explicit Rational(const std::string_view &str);

    explicit Rational(Integer numerator, Integer denominator);

    Rational(Integer rhs);

    Rational(int64_t rhs);

    std::string toString() const override;

    bool equals(const Rational &rhs) const override;

    bool less(const Rational &rhs) const override;

    bool more(const Rational &rhs) const override;

    Rational &add(const Rational &rhs) override;

    Rational &sub(const Rational &rhs) override;

    Rational &neg() override;

    Rational &mul(const Rational &rhs) override;

    Rational &div(const Rational &rhs) override;

    Rational &inc() override;

    Rational &dec() override;

    Rational &round(size_t precision);

    std::string toString(size_t precision) const;

    Integer getInteger() const;

    Integer getNumerator() const;

    Integer getDenominator() const;

  private:
    void fixNegative();

    void fixZero();

    void toIrreducibleRational();

    static void toCommonDenominators(Rational &lhs, Rational &rhs);

    Integer numerator = 0;
    Integer denominator = 1;
    bool sign{};
  };
}
