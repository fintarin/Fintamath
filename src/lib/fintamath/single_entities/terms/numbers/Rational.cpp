/*
  Дробь хранится в виде несократимой дроби (числитель / знаменатель).
*/
#include "single_entities/terms/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

#include "calculator/Calculator.hpp"

constexpr int64_t INITIAL_PRECISION = 36;

using namespace std;

static Integer GCD(const Integer &inA, const Integer &inB);
static Integer LCM(const Integer &a, const Integer &b);

Rational::Rational() {
  this->sign = false;
  this->numerator = 0;
  this->denominator = 1;
}

Rational::Rational(const Rational &other) {
  *this = other;
}

Rational::Rational(const Integer &inLnum) : Rational() {
  this->numerator = inLnum;
  this->checkMinus();
}

Rational::Rational(const Integer &inNumerator, const Integer &inDenominator) : Rational() {
  this->numerator = inNumerator;
  this->denominator = inDenominator;
  this->toIrreducibleRational();
}

Rational::Rational(double inNum) {
  this->toRational(inNum);
}

Rational::Rational(const string &inStr) : Rational() {
  this->toRational(inStr);
}

Rational &Rational::operator=(const Rational &other) {
  this->sign = other.sign;
  this->numerator = other.numerator;
  this->denominator = other.denominator;
  return *this;
}

Rational &Rational::operator=(const Integer &inLnum) {
  *this = Rational(inLnum);
  return *this;
}

Rational &Rational::operator=(double inNum) {
  *this = Rational(inNum);
  return *this;
}

Rational &Rational::operator+=(const Rational &other) {
  Rational otherNum = other;
  this->toCommonDenominators(otherNum);
  this->numerator += otherNum.numerator;
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator+=(const Integer &inLnum) {
  return *this += Rational(inLnum);
}

Rational &Rational::operator+=(int64_t inNum) {
  return *this += Rational(inNum);
}

Rational Rational::operator+(const Rational &other) const {
  Rational thisNum = *this;
  return thisNum += other;
}

Rational operator+(const Rational &other, const Integer &inLnum) {
  return other + Rational(inLnum);
}

Rational operator+(const Integer &inLnum, const Rational &other) {
  return Rational(inLnum) + other;
}

Rational operator+(const Rational &other, int64_t inNum) {
  return other + Rational(inNum);
}

Rational operator+(int64_t inNum, const Rational &other) {
  return Rational(inNum) + other;
}

Rational &Rational::operator-=(const Rational &other) {
  Rational otherNum = other;
  this->toCommonDenominators(otherNum);
  this->numerator -= otherNum.numerator;
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator-=(const Integer &inLnum) {
  return this->operator+=(inLnum * -1);
}

Rational &Rational::operator-=(int64_t inNum) {
  return *this -= Rational(inNum);
}

Rational Rational::operator-(const Rational &other) const {
  Rational thisNum = *this;
  return thisNum -= other;
}

Rational operator-(const Rational &other, const Integer &inLnum) {
  return other - Rational(inLnum);
}

Rational operator-(const Integer &inLnum, const Rational &other) {
  return Rational(inLnum) - other;
}

Rational operator-(const Rational &other, int64_t inNum) {
  return other - Rational(inNum);
}

Rational operator-(int64_t inNum, const Rational &other) {
  return Rational(inNum) - other;
}

Rational &Rational::operator*=(const Rational &other) {
  this->numerator *= other.numerator;
  this->denominator *= other.denominator;
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator*=(const Integer &inLnum) {
  return *this *= Rational(inLnum);
}

Rational &Rational::operator*=(int64_t inNum) {
  return *this *= Rational(inNum);
}

Rational Rational::operator*(const Rational &other) const {
  Rational thisNum = *this;
  return thisNum *= other;
}

Rational operator*(const Rational &other, const Integer &inLnum) {
  return other * Rational(inLnum);
}

Rational operator*(const Integer &inLnum, const Rational &other) {
  return Rational(inLnum) * other;
}

Rational operator*(const Rational &other, int64_t inNum) {
  return other * Rational(inNum);
}

Rational operator*(int64_t inNum, const Rational &other) {
  return Rational(inNum) * other;
}

Rational &Rational::operator/=(const Rational &other) {
  this->numerator *= other.denominator;
  this->denominator *= other.numerator;
  this->sign = !((this->sign && other.sign) || (!this->sign && !other.sign));
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator/=(const Integer &inLnum) {
  return *this /= Rational(inLnum);
}

Rational &Rational::operator/=(int64_t inNum) {
  return *this /= Rational(inNum);
}

Rational Rational::operator/(const Rational &other) const {
  Rational thisNum = *this;
  return thisNum /= other;
}

Rational operator/(const Rational &other, const Integer &inLnum) {
  return other / Rational(inLnum);
}

Rational operator/(const Integer &inLnum, const Rational &other) {
  return Rational(inLnum) / other;
}

Rational operator/(const Rational &other, int64_t inNum) {
  return other / Rational(inNum);
}

Rational operator/(int64_t inNum, const Rational &other) {
  return Rational(inNum) / other;
}

Rational &Rational::operator++() {
  *this += 1;
  return *this;
}

Rational &Rational::operator++(int) {
  *this += 1;
  return *this;
}

Rational &Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational &Rational::operator--(int) {
  *this -= 1;
  return *this;
}

bool Rational::operator==(const Rational &other) const {
  return (this->sign == other.sign && this->numerator == other.numerator && this->denominator == other.denominator);
}

bool operator==(const Rational &other, const Integer &inLnum) {
  return (other == Rational(inLnum));
}

bool operator==(const Integer &inLnum, const Rational &other) {
  return (other == Rational(inLnum));
}

bool operator==(const Rational &other, int64_t inNum) {
  return other == Rational(inNum);
}

bool operator==(int64_t inNum, const Rational &other) {
  return Rational(inNum) == other;
}

bool Rational::operator!=(const Rational &other) const {
  return !(*this == other);
}

bool operator!=(const Rational &other, const Integer &inLnum) {
  return !(other == Rational(inLnum));
}

bool operator!=(const Integer &inLnum, const Rational &other) {
  return !(other == Rational(inLnum));
}

bool operator!=(const Rational &other, int64_t inNum) {
  return other != Rational(inNum);
}

bool operator!=(int64_t inNum, const Rational &other) {
  return Rational(inNum) != other;
}

bool Rational::operator>(const Rational &other) const {
  Rational thisNum = *this;
  Rational otherNum = other;
  thisNum.toCommonDenominators(otherNum);
  return (thisNum.numerator > otherNum.numerator);
}

bool operator>(const Rational &other, const Integer &inLnum) {
  return (other > Rational(inLnum));
}

bool operator>(const Integer &inLnum, const Rational &other) {
  return (Rational(inLnum) > other);
}

bool operator>(const Rational &other, int64_t inNum) {
  return other > Rational(inNum);
}

bool operator>(int64_t inNum, const Rational &other) {
  return Rational(inNum) > other;
}

bool Rational::operator>=(const Rational &other) const {
  return (*this == other || *this > other);
}

bool operator>=(const Rational &other, const Integer &inLnum) {
  return (other >= Rational(inLnum));
}

bool operator>=(const Integer &inLnum, const Rational &other) {
  return (Rational(inLnum) >= other);
}

bool operator>=(const Rational &other, int64_t inNum) {
  return other >= Rational(inNum);
}

bool operator>=(int64_t inNum, const Rational &other) {
  return Rational(inNum) >= other;
}

bool Rational::operator<(const Rational &other) const {
  return !(*this >= other);
}

bool operator<(const Rational &other, const Integer &inLnum) {
  return !(other >= Rational(inLnum));
}

bool operator<(const Integer &inLnum, const Rational &other) {
  return !(Rational(inLnum) >= other);
}

bool operator<(const Rational &other, int64_t inNum) {
  return other < Rational(inNum);
}

bool operator<(int64_t inNum, const Rational &other) {
  return Rational(inNum) < other;
}

bool Rational::operator<=(const Rational &other) const {
  return !(*this > other);
}

bool operator<=(const Rational &other, const Integer &inLnum) {
  return !(other > Rational(inLnum));
}

bool operator<=(const Integer &inLnum, const Rational &other) {
  return !(Rational(inLnum) > other);
}

bool operator<=(const Rational &other, int64_t inNum) {
  return other <= Rational(inNum);
}

bool operator<=(int64_t inNum, const Rational &other) {
  return Rational(inNum) <= other;
}

Integer Rational::getInteger() const {
  return this->numerator / this->denominator;
}

Integer Rational::getNumerator() const {
  return this->numerator % this->denominator;
}

Integer Rational::getDenominator() const {
  return this->denominator;
}

Rational &Rational::toRational(const string &inStr) {
  if (inStr.empty()) {
    throw invalid_argument("Rational invalid input");
  }

  *this = Rational();

  size_t first = 0;
  size_t last = distance(inStr.begin(), find(inStr.begin(), inStr.end(), '.'));

  bool minus = false;
  if (*inStr.begin() == '-') {
    minus = true;
    ++first;
  }

  Integer intPart;
  try {
    intPart = Integer(inStr.substr(first, last - first));
  } catch (const invalid_argument &) {
    throw invalid_argument("Rational invalid input");
  }

  if (last != inStr.size()) {
    try {
      string numeratorStr = inStr.substr(last + 1);
      string denominatorStr(numeratorStr.size() + 1, '0');
      denominatorStr.front() = '1';
      this->numerator = Integer(numeratorStr);
      this->denominator = Integer(denominatorStr);
    } catch (const invalid_argument &) {
      throw invalid_argument("Rational invalid input");
    }
  }

  this->toIrreducibleRational();
  this->numerator += intPart * this->denominator;
  if (this->numerator != 0) {
    this->sign = minus;
  }

  return *this;
}

Rational &Rational::toRational(const Integer &inLnum) {
  *this = inLnum;
  return *this;
}

Rational &Rational::toRational(double inNum) {
  return this->toRational(to_string(inNum));
}

string Rational::toString(size_t precision) const {
  string precStr(precision + 2, '0');
  precStr.front() = '1';

  Integer lnum = this->numerator * Integer(precStr) / this->denominator;
  if (lnum % 10 >= 5) {
    lnum += 10;
  }
  lnum /= 10;

  string res = lnum.toString();
  if (res.size() <= precision) {
    res.insert(res.begin(), precision + 1 - res.size(), '0');
  }
  res.insert(res.end() - (int64_t)precision, '.');

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

Rational &Rational::round(size_t precision) {
  return this->toRational(this->toString(precision));
}

bool Rational::equal(double inNum) const {
  string str;

  if (inNum == 0) {
    str = '0';
  } else {
    str = to_string(inNum);

    while (*(str.end() - 1) == '0') {
      str.pop_back();
    }

    if (*(str.end() - 1) == '.') {
      str.pop_back();
    }
  }

  return (this->toString(6) == str);
}

istream &operator>>(istream &in, Rational &other) {
  string str;
  in >> str;
  other = Rational(str);
  return in;
}

ostream &operator<<(ostream &out, const Rational &other) {
  out << other.toString();
  return out;
}

string Rational::getTypeName() const {
  return "Rational";
}

string Rational::toString() const {
  return this->toString(INITIAL_PRECISION);
}

void Rational::checkZero() {
  if (this->numerator == 0) {
    this->sign = false;
    this->denominator = 1;
    return;
  }
}

void Rational::checkMinus() {
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
Rational &Rational::toIrreducibleRational() {
  if (this->denominator == 0) {
    throw domain_error("Div by zero");
  }

  this->checkMinus();
  Integer gcd = GCD(this->numerator, this->denominator);
  this->numerator /= gcd;
  this->denominator /= gcd;
  this->checkZero();
  return *this;
}

// Приведение двух дробей к общему знаменателю
void Rational::toCommonDenominators(Rational &other) {
  Integer lcm = LCM(this->denominator, other.denominator);

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

// Наибольший общий делитель, используется алгоритм Евклида
inline Integer GCD(const Integer &inA, const Integer &inB) {
  Integer a = inA;
  Integer b = inB;
  while (b != 0) {
    Integer buff = a % b;
    a = b;
    b = buff;
  }
  return a;
}

// Наименьшее общее кратное, используется формула НОК(a, b) = a * b / НОД(a, b)
inline Integer LCM(const Integer &a, const Integer &b) {
  return a * b / GCD(a, b);
}
