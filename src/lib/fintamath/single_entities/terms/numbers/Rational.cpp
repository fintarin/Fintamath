/*
  Дробь хранится в виде несократимой дроби (числитель / знаменатель).
*/
#include "single_entities/terms/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <utility>

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
    firstDigitNum++;
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
      numerator = Integer(numeratorStr);
      denominator = Integer(denominatorStr);
    } catch (const invalid_argument &) {
      throw invalid_argument("Rational invalid input");
    }
  }

  toIrreducibleRational();
  numerator += intPart * denominator;
  if (numerator != 0) {
    sign = isNegative;
  }
}

Rational::Rational(Integer val) : numerator(std::move(val)) {
  fixNegative();
}

Rational::Rational(int64_t val) : numerator(val) {
  fixNegative();
}

Rational::Rational(Integer numerator, Integer denominator)
    : numerator(std::move(numerator)), denominator(std::move(denominator)) {
  toIrreducibleRational();
}

Rational::Rational(int64_t numerator, int64_t denominator) : numerator(numerator), denominator(denominator) {
  toIrreducibleRational();
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
  numerator += tmpRhs.numerator;
  toIrreducibleRational();
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
  numerator -= tmpRhs.numerator;
  toIrreducibleRational();
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
  numerator *= rhs.numerator;
  denominator *= rhs.denominator;
  sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
  toIrreducibleRational();
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
  numerator *= rhs.denominator;
  denominator *= rhs.numerator;
  sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
  toIrreducibleRational();
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
  return val;
}

bool Rational::operator==(const Rational &rhs) const {
  return (sign == rhs.sign && numerator == rhs.numerator && denominator == rhs.denominator);
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
  return numerator / denominator;
}

Integer Rational::getNumerator() const {
  return numerator % denominator;
}

Integer Rational::getDenominator() const {
  return denominator;
}

string Rational::toString(size_t precision) const {
  const int64_t base = 10;
  const int64_t roundUp = 5;

  string precisionStr(precision + 2, '0');
  precisionStr.front() = '1';

  Integer val = numerator * Integer(precisionStr) / denominator;
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

  if (sign) {
    strVal.insert(strVal.begin(), '-');
  }

  return strVal;
}

Rational Rational::round(size_t precision) const {
  return Rational(toString(precision));
}

string Rational::getTypeName() const {
  return "Rational";
}

string Rational::toString() const {
  return toString(INITIAL_PRECISION);
}

void Rational::fixZero() {
  if (numerator == 0) {
    sign = false;
    denominator = 1;
  }
}

void Rational::fixNegative() {
  if (numerator < 0) {
    numerator *= -1;
    sign = !sign;
  }
  if (denominator < 0) {
    denominator *= -1;
    sign = !sign;
  }
}

void Rational::toIrreducibleRational() {
  if (denominator == 0) {
    throw domain_error("Div by zero");
  }
  fixNegative();
  Integer gcdVal = gcd(numerator, denominator);
  numerator /= gcdVal;
  denominator /= gcdVal;
  fixZero();
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
