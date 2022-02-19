#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"

namespace fintamath {
  class Rational : public Number {
  public:
    Rational() = default;
    explicit Rational(const std::string_view &str);
    explicit Rational(Integer rhs);
    explicit Rational(int64_t rhs);
    Rational(Integer numerator, Integer denominator);
    Rational(int64_t numerator, int64_t denominator);

    Rational &operator+=(const Rational &rhs);
    Rational operator+(const Rational &rhs) const;
    Rational &operator-=(const Rational &rhs);
    Rational operator-(const Rational &rhs) const;
    Rational &operator*=(const Rational &rhs);
    Rational operator*(const Rational &rhs) const;
    Rational &operator/=(const Rational &rhs);
    Rational operator/(const Rational &rhs) const;

    Rational &operator++();
    Rational operator++(int);
    Rational &operator--();
    Rational operator--(int);

    Rational operator+() const;
    Rational operator-() const;

    bool operator==(const Rational &rhs) const;
    bool operator!=(const Rational &rhs) const;
    bool operator<(const Rational &rhs) const;
    bool operator>(const Rational &rhs) const;
    bool operator<=(const Rational &rhs) const;
    bool operator>=(const Rational &rhs) const;

    std::string toString() const override;
    std::unique_ptr<Number> minimize() const override;

  private:
    Integer numerator{0};
    Integer denominator{1};
    bool sign{};

    void fixNegative();
    void fixZero();
    void toIrreducibleRational();
    static void toCommonDenominators(Rational &lhs, Rational &rhs);
  };
}
