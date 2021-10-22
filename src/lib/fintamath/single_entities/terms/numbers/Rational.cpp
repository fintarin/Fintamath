/*
  Дробь хранится в виде несократимой дроби (числитель / знаменатель).
*/
#include "single_entities/terms/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

constexpr int64_t STANDARD_PRECISION = 36;

using namespace std;

static Integer gcd(const Integer &lhs, const Integer &rhs);
static Integer lcm(const Integer &lhs, const Integer &rhs);

Rational::Rational(const string &strVal) {
  if (strVal.empty()) {
    throw invalid_argument("Rational invalid input");
  }

  *this = Rational();

  size_t firstDigitNum = 0;
  size_t dotNum = distance(strVal.begin(), find(strVal.begin(), strVal.end(), '.'));

  bool isNegative = false;
  if (*strVal.begin() == '-') {
    isNegative = true;
    ++firstDigitNum;
  }

  Integer intPart;
  try {
    intPart = Integer(strVal.substr(firstDigitNum, dotNum - firstDigitNum));
  } catch (const invalid_argument &) {
    throw invalid_argument("Rational invalid input");
  }

  if (dotNum != strVal.size()) {
    try {
      string numeratorStr = strVal.substr(dotNum + 1);
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
    this->sign = isNegative;
  }
}

Rational::Rational(const Integer &val) {
  this->numerator = val;
  this->checkMinus();
}

Rational::Rational(int64_t val) {
  this->numerator = val;
  this->checkMinus();
}

Rational::Rational(const Integer &inNumerator, const Integer &inDenominator) {
  this->numerator = inNumerator;
  this->denominator = inDenominator;
  this->toIrreducibleRational();
}

Rational::Rational(int64_t inNumerator, int64_t inDenominator) {
  this->numerator = inNumerator;
  this->denominator = inDenominator;
  this->toIrreducibleRational();
}

Rational &Rational::operator=(const Integer &rhs) {
  return *this = Integer(rhs);
}

Rational &Rational::operator=(int64_t rhs) {
  return *this = Integer(rhs);
}

Rational &Rational::operator+=(const Rational &rhs) {
  Rational otherNum = rhs;
  toCommonDenominators(*this, otherNum);
  this->numerator += otherNum.numerator;
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator+=(const Integer &rhs) {
  return *this += Rational(rhs);
}

Rational &Rational::operator+=(int64_t rhs) {
  return *this += Rational(rhs);
}

Rational Rational::operator+(const Rational &rhs) const {
  Rational thisNum = *this;
  return thisNum += rhs;
}

Rational Rational::operator+(const Integer &rhs) const {
  return *this + Rational(rhs);
}

Rational Rational::operator+(int64_t rhs) const {
  return *this + Rational(rhs);
}

Rational operator+(const Integer &lhs, const Rational &rhs) {
  return Rational(lhs) + rhs;
}

Rational operator+(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) + rhs;
}

Rational &Rational::operator-=(const Rational &rhs) {
  Rational otherNum = rhs;
  toCommonDenominators(*this, otherNum);
  this->numerator -= otherNum.numerator;
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator-=(const Integer &rhs) {
  return *this -= Rational(rhs);
}

Rational &Rational::operator-=(int64_t rhs) {
  return *this -= Rational(rhs);
}

Rational Rational::operator-(const Rational &rhs) const {
  Rational thisNum = *this;
  return thisNum -= rhs;
}

Rational Rational::operator-(const Integer &rhs) const {
  return *this - Rational(rhs);
}

Rational Rational::operator-(int64_t rhs) const {
  return *this - Rational(rhs);
}

Rational operator-(const Integer &lhs, const Rational &rhs) {
  return Rational(lhs) - rhs;
}

Rational operator-(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) - rhs;
}

Rational &Rational::operator*=(const Rational &rhs) {
  this->numerator *= rhs.numerator;
  this->denominator *= rhs.denominator;
  this->sign = !((this->sign && rhs.sign) || (!this->sign && !rhs.sign));
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator*=(const Integer &rhs) {
  return *this *= Rational(rhs);
}

Rational &Rational::operator*=(int64_t rhs) {
  return *this *= Rational(rhs);
}

Rational Rational::operator*(const Rational &rhs) const {
  Rational thisNum = *this;
  return thisNum *= rhs;
}

Rational Rational::operator*(const Integer &rhs) const {
  return *this * Rational(rhs);
}

Rational Rational::operator*(int64_t rhs) const {
  return *this * Rational(rhs);
}

Rational operator*(const Integer &lhs, const Rational &rhs) {
  return Rational(lhs) * rhs;
}

Rational operator*(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) * rhs;
}

Rational &Rational::operator/=(const Rational &rhs) {
  this->numerator *= rhs.denominator;
  this->denominator *= rhs.numerator;
  this->sign = !((this->sign && rhs.sign) || (!this->sign && !rhs.sign));
  this->toIrreducibleRational();
  return *this;
}

Rational &Rational::operator/=(const Integer &rhs) {
  return *this /= Rational(rhs);
}

Rational &Rational::operator/=(int64_t rhs) {
  return *this /= Rational(rhs);
}

Rational Rational::operator/(const Rational &rhs) const {
  Rational thisNum = *this;
  return thisNum /= rhs;
}

Rational Rational::operator/(const Integer &rhs) const {
  return *this / Rational(rhs);
}

Rational Rational::operator/(int64_t rhs) const {
  return *this / Rational(rhs);
}

Rational operator/(const Integer &lhs, const Rational &rhs) {
  return Rational(lhs) / rhs;
}

Rational operator/(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) / rhs;
}

Rational &Rational::operator++() {
  *this += 1;
  return *this;
}

Rational Rational::operator++(int) {
  Rational num = *this;
  *this += 1;
  return num;
}

Rational &Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational num = *this;
  *this -= 1;
  return num;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  Rational num = *this;
  num.sign = !num.sign;
  return *this;
}

bool Rational::operator==(const Rational &rhs) const {
  return (this->sign == rhs.sign && this->numerator == rhs.numerator && this->denominator == rhs.denominator);
}

bool Rational::operator==(const Integer &rhs) const {
  return *this == Rational(rhs);
}

bool Rational::Rational::operator==(int64_t rhs) const {
  return *this == Rational(rhs);
}

bool operator==(const Rational &lhs, int64_t rhs) {
  return lhs == Rational(rhs);
}

bool operator==(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) == rhs;
}

bool Rational::operator!=(const Rational &rhs) const {
  return !(*this == rhs);
}

bool Rational::operator!=(const Integer &rhs) const {
  return *this != Rational(rhs);
}

bool Rational::Rational::operator!=(int64_t rhs) const {
  return *this != Rational(rhs);
}

bool operator!=(const Rational &lhs, int64_t rhs) {
  return lhs != Rational(rhs);
}

bool operator!=(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) != rhs;
}

bool Rational::operator<(const Rational &rhs) const {
  Rational thisNum = *this;
  Rational otherNum = rhs;
  toCommonDenominators(thisNum, otherNum);
  return (thisNum.numerator < otherNum.numerator);
}

bool Rational::operator<(const Integer &rhs) const {
  return *this < Rational(rhs);
}

bool Rational::Rational::operator<(int64_t rhs) const {
  return *this < Rational(rhs);
}

bool operator<(const Rational &lhs, int64_t rhs) {
  return lhs < Rational(rhs);
}

bool operator<(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) < rhs;
}

bool Rational::operator>(const Rational &rhs) const {
  Rational thisNum = *this;
  Rational otherNum = rhs;
  toCommonDenominators(thisNum, otherNum);
  return (thisNum.numerator > otherNum.numerator);
}

bool Rational::operator>(const Integer &rhs) const {
  return *this > Rational(rhs);
}

bool Rational::Rational::operator>(int64_t rhs) const {
  return *this > Rational(rhs);
}

bool operator>(const Rational &lhs, int64_t rhs) {
  return lhs > Rational(rhs);
}

bool operator>(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) > rhs;
}

bool Rational::operator<=(const Rational &rhs) const {
  Rational thisNum = *this;
  Rational otherNum = rhs;
  toCommonDenominators(thisNum, otherNum);
  return (thisNum.numerator <= otherNum.numerator);
}

bool Rational::operator<=(const Integer &rhs) const {
  return *this <= Rational(rhs);
}

bool Rational::Rational::operator<=(int64_t rhs) const {
  return *this <= Rational(rhs);
}

bool operator<=(const Rational &lhs, int64_t rhs) {
  return lhs <= Rational(rhs);
}

bool operator<=(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) <= rhs;
}

bool Rational::operator>=(const Rational &rhs) const {
  Rational thisNum = *this;
  Rational otherNum = rhs;
  toCommonDenominators(thisNum, otherNum);
  return (thisNum.numerator >= otherNum.numerator);
}

bool Rational::operator>=(const Integer &rhs) const {
  return *this >= Rational(rhs);
}

bool Rational::Rational::operator>=(int64_t rhs) const {
  return *this >= Rational(rhs);
}

bool operator>=(const Rational &lhs, int64_t rhs) {
  return lhs >= Rational(rhs);
}

bool operator>=(int64_t lhs, const Rational &rhs) {
  return Rational(lhs) >= rhs;
}

istream &operator>>(istream &in, Rational &rhs) {
  string str;
  in >> str;
  rhs = Rational(str);
  return in;
}

ostream &operator<<(ostream &out, const Rational &rhs) {
  out << rhs.toString();
  return out;
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

string Rational::toString(size_t precision) const {
  const int64_t base = 10;
  const int64_t roundUp = 5;

  string precStr(precision + 2, '0');
  precStr.front() = '1';

  Integer lnum = this->numerator * Integer(precStr) / this->denominator;
  if (lnum % base >= roundUp) {
    lnum += base;
  }
  lnum /= base;

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

Rational Rational::round(size_t precision) const {
  return Rational(this->toString(precision));
}

string Rational::getTypeName() const {
  return "Rational";
}

string Rational::toString() const {
  return this->toString(STANDARD_PRECISION);
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

void Rational::toIrreducibleRational() {
  if (this->denominator == 0) {
    throw domain_error("Div by zero");
  }

  this->checkMinus();
  Integer gcdVal = gcd(this->numerator, this->denominator);
  this->numerator /= gcdVal;
  this->denominator /= gcdVal;
  this->checkZero();
}

void Rational::toCommonDenominators(Rational &lhs, Rational &rhs) {
  Integer lcmVal = lcm(lhs.denominator, rhs.denominator);

  if (lhs.sign) {
    lhs.numerator *= -1;
  }
  lhs.numerator *= (lcmVal / lhs.denominator);
  lhs.denominator = lcmVal;
  lhs.sign = false;

  if (rhs.sign) {
    rhs.numerator *= -1;
  }
  rhs.numerator *= (lcmVal / rhs.denominator);
  rhs.denominator = lcmVal;
  rhs.sign = false;
}

// Наибольший общий делитель, используется алгоритм Евклида
inline Integer gcd(const Integer &lhs, const Integer &rhs) {
  Integer tmpLhs = lhs;
  Integer tmpRhs = rhs;
  while (tmpRhs != 0) {
    Integer buff = tmpLhs % tmpRhs;
    tmpLhs = tmpRhs;
    tmpRhs = buff;
  }
  return tmpLhs;
}

// Наименьшее общее кратное, используется формула НОК(a, b) = a * b / НОД(a, b)
inline Integer lcm(const Integer &lhs, const Integer &rhs) {
  return lhs * rhs / gcd(lhs, rhs);
}
