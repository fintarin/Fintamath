#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>

#include "calculator/NodeType.hpp"
#include "numbers/BigInteger.hpp"

class Fraction : public NodeType {
public:
  Fraction();
  Fraction(const Fraction &);
  Fraction(const BigInteger &);
  Fraction(const BigInteger &, const BigInteger &);
  Fraction(double);
  explicit Fraction(const std::string &);

  Fraction &operator=(const Fraction &);
  Fraction &operator=(const BigInteger &);
  Fraction &operator=(double);

  Fraction &operator+=(const Fraction &);
  Fraction &operator+=(const BigInteger &);
  Fraction &operator+=(int64_t);

  Fraction operator+(const Fraction &) const;
  friend Fraction operator+(const Fraction &, const BigInteger &);
  friend Fraction operator+(const BigInteger &, const Fraction &);
  friend Fraction operator+(const Fraction &, int64_t);
  friend Fraction operator+(int64_t, const Fraction &);

  Fraction &operator-=(const Fraction &);
  Fraction &operator-=(const BigInteger &);
  Fraction &operator-=(int64_t);

  Fraction operator-(const Fraction &) const;
  friend Fraction operator-(const Fraction &, const BigInteger &);
  friend Fraction operator-(const BigInteger &, const Fraction &);
  friend Fraction operator-(const Fraction &, int64_t);
  friend Fraction operator-(int64_t, const Fraction &);

  Fraction &operator*=(const Fraction &);
  Fraction &operator*=(const BigInteger &);
  Fraction &operator*=(int64_t);

  Fraction operator*(const Fraction &) const;
  friend Fraction operator*(const Fraction &, const BigInteger &);
  friend Fraction operator*(const BigInteger &, const Fraction &);
  friend Fraction operator*(const Fraction &, int64_t);
  friend Fraction operator*(int64_t, const Fraction &);

  Fraction &operator/=(const Fraction &);
  Fraction &operator/=(const BigInteger &);
  Fraction &operator/=(int64_t);

  Fraction operator/(const Fraction &) const;
  friend Fraction operator/(const Fraction &, const BigInteger &);
  friend Fraction operator/(const BigInteger &, const Fraction &);
  friend Fraction operator/(const Fraction &, int64_t);
  friend Fraction operator/(int64_t, const Fraction &);

  Fraction &operator++();
  Fraction &operator++(int);

  Fraction &operator--();
  Fraction &operator--(int);

  bool operator==(const Fraction &) const;
  friend bool operator==(const Fraction &, const BigInteger &);
  friend bool operator==(const BigInteger &, const Fraction &);
  friend bool operator==(const Fraction &, int64_t);
  friend bool operator==(int64_t, const Fraction &);

  bool operator!=(const Fraction &) const;
  friend bool operator!=(const Fraction &, const BigInteger &);
  friend bool operator!=(const BigInteger &, const Fraction &);
  friend bool operator!=(const Fraction &, int64_t);
  friend bool operator!=(int64_t, const Fraction &);

  bool operator>(const Fraction &) const;
  friend bool operator>(const Fraction &, const BigInteger &);
  friend bool operator>(const BigInteger &, const Fraction &);
  friend bool operator>(const Fraction &, int64_t);
  friend bool operator>(int64_t, const Fraction &);

  bool operator>=(const Fraction &) const;
  friend bool operator>=(const Fraction &, const BigInteger &);
  friend bool operator>=(const BigInteger &, const Fraction &);
  friend bool operator>=(const Fraction &, int64_t);
  friend bool operator>=(int64_t, const Fraction &);

  bool operator<(const Fraction &) const;
  friend bool operator<(const Fraction &, const BigInteger &);
  friend bool operator<(const BigInteger &, const Fraction &);
  friend bool operator<(const Fraction &, int64_t);
  friend bool operator<(int64_t, const Fraction &);

  bool operator<=(const Fraction &) const;
  friend bool operator<=(const Fraction &, const BigInteger &);
  friend bool operator<=(const BigInteger &, const Fraction &);
  friend bool operator<=(const Fraction &, int64_t);
  friend bool operator<=(int64_t, const Fraction &);

  BigInteger getInteger() const;
  BigInteger getNumerator() const;
  BigInteger getDenominator() const;

  Fraction &toFraction(const std::string &);
  Fraction &toFraction(const BigInteger &);
  Fraction &toFraction(double);

  std::string toString(size_t) const;
  Fraction &round(size_t);

  bool equal(double) const;

  friend std::istream &operator>>(std::istream &, Fraction &);
  friend std::ostream &operator<<(std::ostream &, const Fraction &);

  std::string toString() const override;
  std::string getTypeName() const override;

private:
  BigInteger numerator;
  BigInteger denominator;
  bool sign{};

  void checkMinus();
  void checkZero();
  Fraction &toIrreducibleFraction();
  void toCommonDenominators(Fraction &);
};

#endif // FRACTION_HPP