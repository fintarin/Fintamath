#pragma once

#include "fintamath/nodes/numbers/Integer.hpp"

namespace fintamath {
  class Rational : public Node {
  public:
    Rational() = default;
    explicit Rational(const std::string_view &str);
    explicit Rational(Integer numerator, Integer denominator);
    Rational(Integer rhs); // NOLINT

    Rational &operator=(const Integer &rhs);

    Rational &operator+=(const Rational &rhs);
    Rational &operator+=(const Integer &rhs);
    Rational operator+(const Rational &rhs) const;
    Rational operator+(const Integer &rhs) const;
    friend Rational operator+(const Integer &lhs, const Rational &rhs);

    Rational &operator-=(const Rational &rhs);
    Rational &operator-=(const Integer &rhs);
    Rational operator-(const Rational &rhs) const;
    Rational operator-(const Integer &rhs) const;
    friend Rational operator-(const Integer &lhs, const Rational &rhs);

    Rational &operator*=(const Rational &rhs);
    Rational &operator*=(const Integer &rhs);
    Rational operator*(const Rational &rhs) const;
    Rational operator*(const Integer &rhs) const;
    friend Rational operator*(const Integer &lhs, const Rational &rhs);

    Rational &operator/=(const Rational &rhs);
    Rational &operator/=(const Integer &rhs);
    Rational operator/(const Rational &rhs) const;
    Rational operator/(const Integer &rhs) const;
    friend Rational operator/(const Integer &lhs, const Rational &rhs);

    Rational &operator++();
    Rational operator++(int);

    Rational &operator--();
    Rational operator--(int);

    Rational operator+() const;
    Rational operator-() const;

    bool operator==(const Rational &rhs) const;
    bool operator==(const Integer &rhs) const;
    friend bool operator==(const Integer &lhs, const Rational &rhs);

    bool operator!=(const Rational &rhs) const;
    bool operator!=(const Integer &rhs) const;
    friend bool operator!=(const Integer &lhs, const Rational &rhs);

    bool operator<(const Rational &rhs) const;
    bool operator<(const Integer &rhs) const;
    friend bool operator<(const Integer &lhs, const Rational &rhs);

    bool operator>(const Rational &rhs) const;
    bool operator>(const Integer &rhs) const;
    friend bool operator>(const Integer &lhs, const Rational &rhs);

    bool operator<=(const Rational &rhs) const;
    bool operator<=(const Integer &rhs) const;
    friend bool operator<=(const Integer &lhs, const Rational &rhs);

    bool operator>=(const Rational &rhs) const;
    bool operator>=(const Integer &rhs) const;
    friend bool operator>=(const Integer &lhs, const Rational &rhs);

    Integer getInteger() const;
    Integer getNumerator() const;
    Integer getDenominator() const;

    Rational round(size_t precision) const;

    std::string toString() const override;
    std::string toString(size_t precision) const;
    std::shared_ptr<Object> clone() const override;

  private:
    Integer numerator = 0;
    Integer denominator = 1;
    bool sign{};

    void fixNegative();
    void fixZero();
    void toIrreducibleRational();
    static void toCommonDenominators(Rational &lhs, Rational &rhs);
  };
}
