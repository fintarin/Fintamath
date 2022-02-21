#pragma once

#include "fintamath/math_objects/nodes/terms/numbers/Number.hpp"
#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"

class Rational : public Number {
public:
  Rational() = default;
  explicit Rational(const std::string_view &strVal);
  // cppcheck-suppress noExplicitConstructor // NOLINTNEXTLINE
  Rational(Integer val);
  // cppcheck-suppress noExplicitConstructor // NOLINTNEXTLINE
  Rational(int64_t val);
  Rational(Integer numerator, Integer denominator);
  Rational(int64_t numerator, int64_t denominator);

  Rational &operator=(const Integer &rhs);
  Rational &operator=(int64_t rhs);

  Rational &operator+=(const Rational &rhs);
  Rational &operator+=(const Integer &rhs);
  Rational &operator+=(int64_t rhs);
  Rational operator+(const Rational &rhs) const;
  Rational operator+(const Integer &rhs) const;
  Rational operator+(int64_t rhs) const;
  friend Rational operator+(const Integer &lhs, const Rational &rhs);
  friend Rational operator+(int64_t lhs, const Rational &rhs);

  Rational &operator-=(const Rational &rhs);
  Rational &operator-=(const Integer &rhs);
  Rational &operator-=(int64_t rhs);
  Rational operator-(const Rational &rhs) const;
  Rational operator-(const Integer &rhs) const;
  Rational operator-(int64_t rhs) const;
  friend Rational operator-(const Integer &lhs, const Rational &rhs);
  friend Rational operator-(int64_t lhs, const Rational &rhs);

  Rational &operator*=(const Rational &rhs);
  Rational &operator*=(const Integer &rhs);
  Rational &operator*=(int64_t rhs);
  Rational operator*(const Rational &rhs) const;
  Rational operator*(const Integer &rhs) const;
  Rational operator*(int64_t rhs) const;
  friend Rational operator*(const Integer &lhs, const Rational &rhs);
  friend Rational operator*(int64_t lhs, const Rational &rhs);

  Rational &operator/=(const Rational &rhs);
  Rational &operator/=(const Integer &rhs);
  Rational &operator/=(int64_t rhs);
  Rational operator/(const Rational &rhs) const;
  Rational operator/(const Integer &rhs) const;
  Rational operator/(int64_t rhs) const;
  friend Rational operator/(const Integer &lhs, const Rational &rhs);
  friend Rational operator/(int64_t lhs, const Rational &rhs);

  Rational &operator++();
  Rational operator++(int);

  Rational &operator--();
  Rational operator--(int);

  Rational operator+() const;
  Rational operator-() const;

  bool operator==(const Rational &rhs) const;
  bool operator==(const Integer &rhs) const;
  bool operator==(int64_t rhs) const;
  friend bool operator==(const Integer &lhs, const Rational &rhs);
  friend bool operator==(int64_t lhs, const Rational &rhs);

  bool operator!=(const Rational &rhs) const;
  bool operator!=(const Integer &rhs) const;
  bool operator!=(int64_t rhs) const;
  friend bool operator!=(const Integer &lhs, const Rational &rhs);
  friend bool operator!=(int64_t lhs, const Rational &rhs);

  bool operator<(const Rational &rhs) const;
  bool operator<(const Integer &rhs) const;
  bool operator<(int64_t rhs) const;
  friend bool operator<(const Integer &lhs, const Rational &rhs);
  friend bool operator<(int64_t lhs, const Rational &rhs);

  bool operator>(const Rational &rhs) const;
  bool operator>(const Integer &rhs) const;
  bool operator>(int64_t rhs) const;
  friend bool operator>(const Integer &lhs, const Rational &rhs);
  friend bool operator>(int64_t lhs, const Rational &rhs);

  bool operator<=(const Rational &rhs) const;
  bool operator<=(const Integer &rhs) const;
  bool operator<=(int64_t rhs) const;
  friend bool operator<=(const Integer &lhs, const Rational &rhs);
  friend bool operator<=(int64_t lhs, const Rational &rhs);

  bool operator>=(const Rational &rhs) const;
  bool operator>=(const Integer &rhs) const;
  bool operator>=(int64_t rhs) const;
  friend bool operator>=(const Integer &lhs, const Rational &rhs);
  friend bool operator>=(int64_t lhs, const Rational &rhs);

  friend std::istream &operator>>(std::istream &in, Rational &rhs);
  friend std::ostream &operator<<(std::ostream &out, const Rational &rhs);

  Integer getInteger() const;
  Integer getNumerator() const;
  Integer getDenominator() const;

  Rational round(size_t precision) const;

  std::string toString() const override;
  std::string toString(size_t precision) const;

private:
  Integer numerator = 0;
  Integer denominator = 1;
  bool sign{};

  void fixNegative();
  void fixZero();
  void toIrreducibleRational();
  static void toCommonDenominators(Rational &lhs, Rational &rhs);
};
