#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <string>

#include "single_entities/ISingleEntity.hpp"
#include "single_entities/terms/numbers/Integer.hpp"

class Rational : public ISingleEntity {
public:
  Rational();
  Rational(const Rational &);
  Rational(const Integer &);
  Rational(const Integer &, const Integer &);
  Rational(double);
  explicit Rational(const std::string &);

  Rational &operator=(const Rational &);
  Rational &operator=(const Integer &);
  Rational &operator=(double);

  Rational &operator+=(const Rational &);
  Rational &operator+=(const Integer &);
  Rational &operator+=(int64_t);

  Rational operator+(const Rational &) const;
  friend Rational operator+(const Rational &, const Integer &);
  friend Rational operator+(const Integer &, const Rational &);
  friend Rational operator+(const Rational &, int64_t);
  friend Rational operator+(int64_t, const Rational &);

  Rational &operator-=(const Rational &);
  Rational &operator-=(const Integer &);
  Rational &operator-=(int64_t);

  Rational operator-(const Rational &) const;
  friend Rational operator-(const Rational &, const Integer &);
  friend Rational operator-(const Integer &, const Rational &);
  friend Rational operator-(const Rational &, int64_t);
  friend Rational operator-(int64_t, const Rational &);

  Rational &operator*=(const Rational &);
  Rational &operator*=(const Integer &);
  Rational &operator*=(int64_t);

  Rational operator*(const Rational &) const;
  friend Rational operator*(const Rational &, const Integer &);
  friend Rational operator*(const Integer &, const Rational &);
  friend Rational operator*(const Rational &, int64_t);
  friend Rational operator*(int64_t, const Rational &);

  Rational &operator/=(const Rational &);
  Rational &operator/=(const Integer &);
  Rational &operator/=(int64_t);

  Rational operator/(const Rational &) const;
  friend Rational operator/(const Rational &, const Integer &);
  friend Rational operator/(const Integer &, const Rational &);
  friend Rational operator/(const Rational &, int64_t);
  friend Rational operator/(int64_t, const Rational &);

  Rational &operator++();
  Rational &operator++(int);

  Rational &operator--();
  Rational &operator--(int);

  bool operator==(const Rational &) const;
  friend bool operator==(const Rational &, const Integer &);
  friend bool operator==(const Integer &, const Rational &);
  friend bool operator==(const Rational &, int64_t);
  friend bool operator==(int64_t, const Rational &);

  bool operator!=(const Rational &) const;
  friend bool operator!=(const Rational &, const Integer &);
  friend bool operator!=(const Integer &, const Rational &);
  friend bool operator!=(const Rational &, int64_t);
  friend bool operator!=(int64_t, const Rational &);

  bool operator>(const Rational &) const;
  friend bool operator>(const Rational &, const Integer &);
  friend bool operator>(const Integer &, const Rational &);
  friend bool operator>(const Rational &, int64_t);
  friend bool operator>(int64_t, const Rational &);

  bool operator>=(const Rational &) const;
  friend bool operator>=(const Rational &, const Integer &);
  friend bool operator>=(const Integer &, const Rational &);
  friend bool operator>=(const Rational &, int64_t);
  friend bool operator>=(int64_t, const Rational &);

  bool operator<(const Rational &) const;
  friend bool operator<(const Rational &, const Integer &);
  friend bool operator<(const Integer &, const Rational &);
  friend bool operator<(const Rational &, int64_t);
  friend bool operator<(int64_t, const Rational &);

  bool operator<=(const Rational &) const;
  friend bool operator<=(const Rational &, const Integer &);
  friend bool operator<=(const Integer &, const Rational &);
  friend bool operator<=(const Rational &, int64_t);
  friend bool operator<=(int64_t, const Rational &);

  Integer getInteger() const;
  Integer getNumerator() const;
  Integer getDenominator() const;

  Rational &toRational(const std::string &);
  Rational &toRational(const Integer &);
  Rational &toRational(double);

  std::string toString(size_t) const;
  Rational &round(size_t);

  bool equal(double) const;

  friend std::istream &operator>>(std::istream &, Rational &);
  friend std::ostream &operator<<(std::ostream &, const Rational &);

  std::string toString() const override;
  std::string getTypeName() const override;

private:
  Integer numerator;
  Integer denominator;
  bool sign{};

  void checkMinus();
  void checkZero();
  Rational &toIrreducibleRational();
  void toCommonDenominators(Rational &);
};

#endif // RATIONAL_HPP
