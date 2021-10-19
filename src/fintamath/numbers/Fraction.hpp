#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>

#include "calculator/NodeType.hpp"
#include "numbers/BigInteger.hpp"

class Fraction : public NodeType {
private:
  void checkMinus();
  void checkZero();
  Fraction &toIrreducibleFraction();
  void toCommonDenominators(Fraction &);

public:
  Fraction();
  Fraction(const Fraction &);
  Fraction(const BigInteger &);
  Fraction(const BigInteger &, const BigInteger &);
  Fraction(const double);
  explicit Fraction(const std::string &);

  Fraction &operator=(const Fraction &);
  Fraction &operator=(const BigInteger &);
  Fraction &operator=(const double);

  Fraction &operator+=(const Fraction &);
  Fraction &operator+=(const BigInteger &);
  Fraction &operator+=(const long long);

  Fraction operator+(const Fraction &) const;
  friend Fraction operator+(const Fraction &, const BigInteger &);
  friend Fraction operator+(const BigInteger &, const Fraction &);
  friend Fraction operator+(const Fraction &, const long long);
  friend Fraction operator+(const long long, const Fraction &);

  Fraction &operator-=(const Fraction &);
  Fraction &operator-=(const BigInteger &);
  Fraction &operator-=(const long long);

  Fraction operator-(const Fraction &) const;
  friend Fraction operator-(const Fraction &, const BigInteger &);
  friend Fraction operator-(const BigInteger &, const Fraction &);
  friend Fraction operator-(const Fraction &, const long long);
  friend Fraction operator-(const long long, const Fraction &);

  Fraction &operator*=(const Fraction &);
  Fraction &operator*=(const BigInteger &);
  Fraction &operator*=(const long long);

  Fraction operator*(const Fraction &) const;
  friend Fraction operator*(const Fraction &, const BigInteger &);
  friend Fraction operator*(const BigInteger &, const Fraction &);
  friend Fraction operator*(const Fraction &, const long long);
  friend Fraction operator*(const long long, const Fraction &);

  Fraction &operator/=(const Fraction &);
  Fraction &operator/=(const BigInteger &);
  Fraction &operator/=(const long long);

  Fraction operator/(const Fraction &) const;
  friend Fraction operator/(const Fraction &, const BigInteger &);
  friend Fraction operator/(const BigInteger &, const Fraction &);
  friend Fraction operator/(const Fraction &, const long long);
  friend Fraction operator/(const long long, const Fraction &);

  Fraction &operator++();
  Fraction &operator++(int);

  Fraction &operator--();
  Fraction &operator--(int);

  bool operator==(const Fraction &) const;
  friend bool operator==(const Fraction &, const BigInteger &);
  friend bool operator==(const BigInteger &, const Fraction &);
  friend bool operator==(const Fraction &, const long long);
  friend bool operator==(const long long, const Fraction &);

  bool operator!=(const Fraction &) const;
  friend bool operator!=(const Fraction &, const BigInteger &);
  friend bool operator!=(const BigInteger &, const Fraction &);
  friend bool operator!=(const Fraction &, const long long);
  friend bool operator!=(const long long, const Fraction &);

  bool operator>(const Fraction &) const;
  friend bool operator>(const Fraction &, const BigInteger &);
  friend bool operator>(const BigInteger &, const Fraction &);
  friend bool operator>(const Fraction &, const long long);
  friend bool operator>(const long long, const Fraction &);

  bool operator>=(const Fraction &) const;
  friend bool operator>=(const Fraction &, const BigInteger &);
  friend bool operator>=(const BigInteger &, const Fraction &);
  friend bool operator>=(const Fraction &, const long long);
  friend bool operator>=(const long long, const Fraction &);

  bool operator<(const Fraction &) const;
  friend bool operator<(const Fraction &, const BigInteger &);
  friend bool operator<(const BigInteger &, const Fraction &);
  friend bool operator<(const Fraction &, const long long);
  friend bool operator<(const long long, const Fraction &);

  bool operator<=(const Fraction &) const;
  friend bool operator<=(const Fraction &, const BigInteger &);
  friend bool operator<=(const BigInteger &, const Fraction &);
  friend bool operator<=(const Fraction &, const long long);
  friend bool operator<=(const long long, const Fraction &);

  BigInteger getInteger() const;
  BigInteger getNumerator() const;
  BigInteger getDenominator() const;

  Fraction &toFraction(const std::string &);
  Fraction &toFraction(const BigInteger &);
  Fraction &toFraction(const double);

  const std::string toString(const size_t) const;
  Fraction &round(const size_t);

  bool equal(const double) const;

  friend std::istream &operator>>(std::istream &, Fraction &);
  friend std::ostream &operator<<(std::ostream &, const Fraction &);

  const std::string toString() const override;
  const std::string getTypeName() const override;

private:
  BigInteger numerator;
  BigInteger denominator;
  bool sign;
};

#endif // FRACTION_HPP