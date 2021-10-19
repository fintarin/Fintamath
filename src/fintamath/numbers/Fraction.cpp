/*
  Дробь хранится в виде несократимой дроби (числитель / знаменатель).
*/
#include "numbers/Fraction.hpp"

#include <algorithm>
#include <string>

#include "calculator/Calculator.hpp"
#include "calculator/ExceptionClasses.hpp"

// Наибольший общий делитель, используется алгоритм Евклида
BigInteger GCD(const BigInteger &inA, const BigInteger &inB) {
  BigInteger a = inA, b = inB;
  while (b != 0) {
    BigInteger buff = a % b;
    a = b;
    b = buff;
  }
  return a;
}

// Наименьшее общее кратное, используется формула НОК(a, b) = a * b / НОД(a, b)
BigInteger LCM(const BigInteger &a, const BigInteger &b) {
  return a * b / GCD(a, b);
}

void Fraction::checkZero() {
  if (this->numerator == 0) {
    this->sign = false;
    this->denominator = 1;
    return;
  }
}

void Fraction::checkMinus() {
  if (this->numerator < 0) {
    this->numerator *= -1;
    this->sign = !this->sign;
  }
  if (this->denominator < 0) {
    this->denominator *= -1;
    this->sign = !this->sign;
  }
}

// Сокращение дроби
Fraction &Fraction::toIrreducibleFraction() {
  if (this->denominator == 0) {
    throw DividedByZero("div||mod");
  }

  this->checkMinus();
  BigInteger gcd = GCD(this->numerator, this->denominator);
  this->numerator /= gcd;
  this->denominator /= gcd;
  this->checkZero();
  return *this;
}

// Приведение двух дробей к общему знаменателю
void Fraction::toCommonDenominators(Fraction &other) {
  BigInteger lcm = LCM(this->denominator, other.denominator);

  if (this->sign) {
    this->numerator *= -1;
  }
  this->numerator *= (lcm / this->denominator);
  this->denominator = lcm;
  this->sign = false;

  if (other.sign) {
    other.numerator *= -1;
  }
  other.numerator *= (lcm / other.denominator);
  other.denominator = lcm;
  other.sign = false;
}

Fraction::Fraction() {
  this->sign = false;
  this->numerator = 0;
  this->denominator = 1;
}

Fraction::Fraction(const Fraction &other) {
  *this = other;
}

Fraction::Fraction(const BigInteger &inLnum) : Fraction() {
  this->numerator = inLnum;
  this->checkMinus();
}

Fraction::Fraction(const BigInteger &inNumerator, const BigInteger &inDenominator) : Fraction() {
  this->numerator = inNumerator;
  this->denominator = inDenominator;
  this->toIrreducibleFraction();
}

Fraction::Fraction(double inNum) {
  this->toFraction(inNum);
}

Fraction::Fraction(const std::string &inStr) : Fraction() {
  this->toFraction(inStr);
}

Fraction &Fraction::operator=(const Fraction &other) {
  this->sign = other.sign;
  this->numerator = other.numerator;
  this->denominator = other.denominator;
  return *this;
}

Fraction &Fraction::operator=(const BigInteger &inLnum) {
  *this = Fraction(inLnum);
  return *this;
}

Fraction &Fraction::operator=(double inNum) {
  *this = Fraction(inNum);
  return *this;
}

Fraction &Fraction::operator+=(const Fraction &other) {
  Fraction otherNum = other;
  this->toCommonDenominators(otherNum);
  this->numerator += otherNum.numerator;
  this->toIrreducibleFraction();
  return *this;
}

Fraction &Fraction::operator+=(const BigInteger &inLnum) {
  return *this += Fraction(inLnum);
}

Fraction &Fraction::operator+=(int64_t inNum) {
  return *this += Fraction(inNum);
}

Fraction Fraction::operator+(const Fraction &other) const {
  Fraction thisNum = *this;
  return thisNum += other;
}

Fraction operator+(const Fraction &other, const BigInteger &inLnum) {
  return other + Fraction(inLnum);
}

Fraction operator+(const BigInteger &inLnum, const Fraction &other) {
  return Fraction(inLnum) + other;
}

Fraction operator+(const Fraction &other, int64_t inNum) {
  return other + Fraction(inNum);
}

Fraction operator+(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) + other;
}

Fraction &Fraction::operator-=(const Fraction &other) {
  Fraction otherNum = other;
  this->toCommonDenominators(otherNum);
  this->numerator -= otherNum.numerator;
  this->toIrreducibleFraction();
  return *this;
}

Fraction &Fraction::operator-=(const BigInteger &inLnum) {
  return this->operator+=(inLnum * -1);
}

Fraction &Fraction::operator-=(int64_t inNum) {
  return *this -= Fraction(inNum);
}

Fraction Fraction::operator-(const Fraction &other) const {
  Fraction thisNum = *this;
  return thisNum -= other;
}

Fraction operator-(const Fraction &other, const BigInteger &inLnum) {
  return other - Fraction(inLnum);
}

Fraction operator-(const BigInteger &inLnum, const Fraction &other) {
  return Fraction(inLnum) - other;
}

Fraction operator-(const Fraction &other, int64_t inNum) {
  return other - Fraction(inNum);
}

Fraction operator-(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) - other;
}

Fraction &Fraction::operator*=(const Fraction &other) {
  this->numerator *= other.numerator;
  this->denominator *= other.denominator;
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));
  this->toIrreducibleFraction();
  return *this;
}

Fraction &Fraction::operator*=(const BigInteger &inLnum) {
  return *this *= Fraction(inLnum);
}

Fraction &Fraction::operator*=(int64_t inNum) {
  return *this *= Fraction(inNum);
}

Fraction Fraction::operator*(const Fraction &other) const {
  Fraction thisNum = *this;
  return thisNum *= other;
}

Fraction operator*(const Fraction &other, const BigInteger &inLnum) {
  return other * Fraction(inLnum);
}

Fraction operator*(const BigInteger &inLnum, const Fraction &other) {
  return Fraction(inLnum) * other;
}

Fraction operator*(const Fraction &other, int64_t inNum) {
  return other * Fraction(inNum);
}

Fraction operator*(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) * other;
}

Fraction &Fraction::operator/=(const Fraction &other) {
  this->numerator *= other.denominator;
  this->denominator *= other.numerator;
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));
  this->toIrreducibleFraction();
  return *this;
}

Fraction &Fraction::operator/=(const BigInteger &inLnum) {
  return *this /= Fraction(inLnum);
}

Fraction &Fraction::operator/=(int64_t inNum) {
  return *this /= Fraction(inNum);
}

Fraction Fraction::operator/(const Fraction &other) const {
  Fraction thisNum = *this;
  return thisNum /= other;
}

Fraction operator/(const Fraction &other, const BigInteger &inLnum) {
  return other / Fraction(inLnum);
}

Fraction operator/(const BigInteger &inLnum, const Fraction &other) {
  return Fraction(inLnum) / other;
}

Fraction operator/(const Fraction &other, int64_t inNum) {
  return other / Fraction(inNum);
}

Fraction operator/(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) / other;
}

Fraction &Fraction::operator++() {
  *this += 1;
  return *this;
}

Fraction &Fraction::operator++(int) {
  *this += 1;
  return *this;
}

Fraction &Fraction::operator--() {
  *this -= 1;
  return *this;
}

Fraction &Fraction::operator--(int) {
  *this -= 1;
  return *this;
}

bool Fraction::operator==(const Fraction &other) const {
  return (this->sign == other.sign && this->numerator == other.numerator && this->denominator == other.denominator);
}

bool operator==(const Fraction &other, const BigInteger &inLnum) {
  return (other == Fraction(inLnum));
}

bool operator==(const BigInteger &inLnum, const Fraction &other) {
  return (other == Fraction(inLnum));
}

bool operator==(const Fraction &other, int64_t inNum) {
  return other == Fraction(inNum);
}

bool operator==(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) == other;
}

bool Fraction::operator!=(const Fraction &other) const {
  return !(*this == other);
}

bool operator!=(const Fraction &other, const BigInteger &inLnum) {
  return !(other == Fraction(inLnum));
}

bool operator!=(const BigInteger &inLnum, const Fraction &other) {
  return !(other == Fraction(inLnum));
}

bool operator!=(const Fraction &other, int64_t inNum) {
  return other != Fraction(inNum);
}

bool operator!=(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) != other;
}

bool Fraction::operator>(const Fraction &other) const {
  Fraction thisNum = *this, otherNum = other;
  thisNum.toCommonDenominators(otherNum);
  return (thisNum.numerator > otherNum.numerator);
}

bool operator>(const Fraction &other, const BigInteger &inLnum) {
  return (other > Fraction(inLnum));
}

bool operator>(const BigInteger &inLnum, const Fraction &other) {
  return (Fraction(inLnum) > other);
}

bool operator>(const Fraction &other, int64_t inNum) {
  return other > Fraction(inNum);
}

bool operator>(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) > other;
}

bool Fraction::operator>=(const Fraction &other) const {
  return (*this == other || *this > other);
}

bool operator>=(const Fraction &other, const BigInteger &inLnum) {
  return (other >= Fraction(inLnum));
}

bool operator>=(const BigInteger &inLnum, const Fraction &other) {
  return (Fraction(inLnum) >= other);
}

bool operator>=(const Fraction &other, int64_t inNum) {
  return other >= Fraction(inNum);
}

bool operator>=(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) >= other;
}

bool Fraction::operator<(const Fraction &other) const {
  return !(*this >= other);
}

bool operator<(const Fraction &other, const BigInteger &inLnum) {
  return !(other >= Fraction(inLnum));
}

bool operator<(const BigInteger &inLnum, const Fraction &other) {
  return !(Fraction(inLnum) >= other);
}

bool operator<(const Fraction &other, int64_t inNum) {
  return other < Fraction(inNum);
}

bool operator<(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) < other;
}

bool Fraction::operator<=(const Fraction &other) const {
  return !(*this > other);
}

bool operator<=(const Fraction &other, const BigInteger &inLnum) {
  return !(other > Fraction(inLnum));
}

bool operator<=(const BigInteger &inLnum, const Fraction &other) {
  return !(Fraction(inLnum) > other);
}

bool operator<=(const Fraction &other, int64_t inNum) {
  return other <= Fraction(inNum);
}

bool operator<=(int64_t inNum, const Fraction &other) {
  return Fraction(inNum) <= other;
}

BigInteger Fraction::getInteger() const {
  return this->numerator / this->denominator;
}

BigInteger Fraction::getNumerator() const {
  return this->numerator % this->denominator;
}

BigInteger Fraction::getDenominator() const {
  return this->denominator;
}

Fraction &Fraction::toFraction(const std::string &inStr) {
  if (inStr == "") {
    throw IncorrectInput("Fraction");
  }

  *this = Fraction();

  size_t first = 0;
  size_t last = std::distance(inStr.begin(), std::find(inStr.begin(), inStr.end(), '.'));

  bool minus = false;
  if (*inStr.begin() == '-') {
    minus = true;
    ++first;
  }

  BigInteger intPart;
  try {
    intPart = BigInteger(inStr.substr(first, last - first));
  } catch (IncorrectInput) {
    throw IncorrectInput("Fraction");
  }

  if (last != inStr.size()) {
    try {
      std::string numeratorStr = inStr.substr(last + 1);
      std::string denominatorStr(numeratorStr.size() + 1, '0');
      denominatorStr.front() = '1';
      this->numerator = BigInteger(numeratorStr);
      this->denominator = BigInteger(denominatorStr);
    } catch (IncorrectInput) {
      throw IncorrectInput("Fraction");
    }
  }

  this->toIrreducibleFraction();
  this->numerator += intPart * this->denominator;
  if (this->numerator != 0) {
    this->sign = minus;
  }

  return *this;
}

Fraction &Fraction::toFraction(const BigInteger &inLnum) {
  *this = inLnum;
  return *this;
}

Fraction &Fraction::toFraction(double inNum) {
  return this->toFraction(std::to_string(inNum));
}

std::string Fraction::toString(size_t precision) const {
  std::string precStr(precision + 2, '0');
  precStr.front() = '1';

  BigInteger lnum = this->numerator * BigInteger(precStr) / this->denominator;
  if (lnum % 10 >= 5) {
    lnum += 10;
  }
  lnum /= 10;

  std::string res = lnum.toString();
  if (res.size() <= precision) {
    res.insert(res.begin(), precision + 1 - res.size(), '0');
  }
  res.insert(res.end() - precision, '.');

  while (!res.empty() && res.back() == '0') {
    res.pop_back();
  }
  while (res[0] == '0' && res[1] != '.') {
    res.erase(res.begin());
  }
  if (res.back() == '.') {
    res.pop_back();
  }

  if (this->sign) {
    res.insert(res.begin(), '-');
  }

  return res;
}

Fraction &Fraction::round(size_t precision) {
  return this->toFraction(this->toString(precision));
}

bool Fraction::equal(double inNum) const {
  std::string str;

  if (inNum == 0) {
    str = '0';
  } else {
    str = std::to_string(inNum);

    while (*(str.end() - 1) == '0') {
      str.pop_back();
    }

    if (*(str.end() - 1) == '.') {
      str.pop_back();
    }
  }

  return (this->toString(6) == str);
}

std::istream &operator>>(std::istream &in, Fraction &other) {
  std::string str;
  in >> str;
  other = Fraction(str);
  return in;
}

std::ostream &operator<<(std::ostream &out, const Fraction &other) {
  out << other.toString();
  return out;
}

std::string Fraction::getTypeName() const {
  return "Fraction";
}

std::string Fraction::toString() const {
  return this->toString(PRECISION);
}
