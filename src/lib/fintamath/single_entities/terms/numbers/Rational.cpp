/*
  Дробь хранится в виде несократимой дроби (числитель / знаменатель).
*/
#include "single_entities/terms/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>

constexpr int64_t INITIAL_PRECISION = 36;

using namespace std;

static Integer gcd(const Integer &lhs, const Integer &rhs);
static Integer lcm(const Integer &lhs, const Integer &rhs);

Rational::Rational(const string &strVal) {
  if (strVal.empty()) {
    throw invalid_argument("Rational invalid input");
  }

  size_t firstDigitNum = 0;
  size_t firstDotNum = distance(strVal.begin(), find(strVal.begin(), strVal.end(), '.'));

  bool isNegative = false;
  if (strVal.front() == '-') {
    isNegative = true;
    ++firstDigitNum;
  }

  Integer intPart;
  try {
    intPart = Integer(strVal.substr(firstDigitNum, firstDotNum - firstDigitNum));
  } catch (const invalid_argument &) {
    throw invalid_argument("Rational invalid input");
  }

  if (firstDotNum != strVal.size()) {
    try {
      string numeratorStr = strVal.substr(firstDotNum + 1);
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
  this->fixNegative();
}

Rational::Rational(int64_t val) {
  this->numerator = val;
  this->fixNegative();
}

Rational::Rational(const Integer &numerator, const Integer &denominator) {
  this->numerator = numerator;
  this->denominator = denominator;
  this->toIrreducibleRational();
}

Rational::Rational(int64_t numerator, int64_t denominator) : Rational(Integer(numerator), Integer(denominator)) {
}

Rational &Rational::operator=(const Integer &rhs) {
  return *this = Rational(rhs);
}

Rational &Rational::operator=(int64_t rhs) {
  return *this = Rational(rhs);
}

Rational &Rational::operator+=(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  this->numerator += tmpRhs.numerator;
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
  Rational lhs = *this;
  return lhs += rhs;
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
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  this->numerator -= tmpRhs.numerator;
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
  Rational lhs = *this;
  return lhs -= rhs;
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
  Rational lhs = *this;
  return lhs *= rhs;
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
  Rational lhs = *this;
  return lhs /= rhs;
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
  Rational val = *this;
  *this += 1;
  return val;
}

Rational &Rational::operator--() {
  *this -= 1;
  return *this;
}

Rational Rational::operator--(int) {
  Rational val = *this;
  *this -= 1;
  return val;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  Rational val = *this;
  val.sign = !val.sign;
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
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator < tmpRhs.numerator);
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
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator > tmpRhs.numerator);
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
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator <= tmpRhs.numerator);
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
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator >= tmpRhs.numerator);
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
  string strVal;
  in >> strVal;
  rhs = Rational(strVal);
  return in;
}

ostream &operator<<(ostream &out, const Rational &rhs) {
  return out << rhs.toString();
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

  string precisionStr(precision + 2, '0');
  precisionStr.front() = '1';

  Integer val = this->numerator * Integer(precisionStr) / this->denominator;
  if (val % base >= roundUp) {
    val += base;
  }
  val /= base;

  string strVal = val.toString();
  if (strVal.size() <= precision) {
    strVal.insert(strVal.begin(), precision + 1 - strVal.size(), '0');
  }
  strVal.insert(strVal.end() - (int64_t)precision, '.');

  while (!strVal.empty() && strVal.back() == '0') {
    strVal.pop_back();
  }
  while (strVal[0] == '0' && strVal[1] != '.') {
    strVal.erase(strVal.begin());
  }
  if (strVal.back() == '.') {
    strVal.pop_back();
  }

  if (this->sign) {
    strVal.insert(strVal.begin(), '-');
  }

  return strVal;
}

Rational Rational::round(size_t precision) const {
  return Rational(this->toString(precision));
}

string Rational::getTypeName() const {
  return "Rational";
}

string Rational::toString() const {
  return this->toString(INITIAL_PRECISION);
}

void Rational::fixZero() {
  if (this->numerator == 0) {
    this->sign = false;
    this->denominator = 1;
  }
}

void Rational::fixNegative() {
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
  this->fixNegative();
  Integer gcdVal = gcd(this->numerator, this->denominator);
  this->numerator /= gcdVal;
  this->denominator /= gcdVal;
  this->fixZero();
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
static Integer gcd(const Integer &lhs, const Integer &rhs) {
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
static Integer lcm(const Integer &lhs, const Integer &rhs) {
  return lhs * rhs / gcd(lhs, rhs);
}
