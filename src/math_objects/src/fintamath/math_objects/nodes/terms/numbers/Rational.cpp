#include "fintamath/math_objects/nodes/terms/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>

using namespace fintamath;

static Integer gcd(const Integer &lhs, const Integer &rhs);
static Integer lcm(const Integer &lhs, const Integer &rhs);

Rational::Rational(const std::string_view &str) {
  if (str.empty()) {
    throw std::invalid_argument("Rational invalid input");
  }

  size_t firstDigitNum = 0;
  size_t firstDotNum = std::distance(str.begin(), std::find(str.begin(), str.end(), '.'));

  bool isNegative = false;
  if (str.front() == '-') {
    isNegative = true;
    firstDigitNum++;
  }

  Integer intPart;
  try {
    intPart = Integer(str.substr(firstDigitNum, firstDotNum - firstDigitNum));
  } catch (const std::invalid_argument &) {
    throw std::invalid_argument("Rational invalid input");
  }

  if (firstDotNum != str.size()) {
    try {
      auto numeratorStr = str.substr(firstDotNum + 1);
      std::string denominatorStr(numeratorStr.size() + 1, '0');
      denominatorStr.front() = '1';
      numerator = Integer(numeratorStr);
      denominator = Integer(denominatorStr);
    } catch (const std::invalid_argument &) {
      throw std::invalid_argument("Rational invalid input");
    }
  }

  toIrreducibleRational();
  numerator += intPart * denominator;
  if (numerator != Integer(0)) {
    sign = isNegative;
  }
}

Rational::Rational(Integer rhs) : numerator(std::move(rhs)) {
  fixNegative();
}

Rational::Rational(int64_t rhs) : numerator(rhs) {
  fixNegative();
}

Rational::Rational(Integer numerator, Integer denominator)
    : numerator(std::move(numerator)), denominator(std::move(denominator)) {
  toIrreducibleRational();
}

Rational::Rational(int64_t numerator, int64_t denominator) : numerator(numerator), denominator(denominator) {
  toIrreducibleRational();
}

Rational &Rational::operator+=(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numerator += tmpRhs.numerator;
  toIrreducibleRational();
  return *this;
}

Rational Rational::operator+(const Rational &rhs) const {
  Rational lhs = *this;
  return lhs += rhs;
}

Rational &Rational::operator-=(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numerator -= tmpRhs.numerator;
  toIrreducibleRational();
  return *this;
}

Rational Rational::operator-(const Rational &rhs) const {
  Rational lhs = *this;
  return lhs -= rhs;
}

Rational &Rational::operator*=(const Rational &rhs) {
  numerator *= rhs.numerator;
  denominator *= rhs.denominator;
  sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
  toIrreducibleRational();
  return *this;
}

Rational Rational::operator*(const Rational &rhs) const {
  Rational lhs = *this;
  return lhs *= rhs;
}

Rational &Rational::operator/=(const Rational &rhs) {
  numerator *= rhs.denominator;
  denominator *= rhs.numerator;
  sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
  toIrreducibleRational();
  return *this;
}

Rational Rational::operator/(const Rational &rhs) const {
  Rational lhs = *this;
  return lhs /= rhs;
}

Rational &Rational::operator++() {
  return *this += Rational(1);
}

Rational Rational::operator++(int) {
  Rational val = *this;
  *this += Rational(1);
  return val;
}

Rational &Rational::operator--() {
  return *this -= Rational(1);
}

Rational Rational::operator--(int) {
  Rational val = *this;
  *this -= Rational(1);
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

bool Rational::operator!=(const Rational &rhs) const {
  return !(*this == rhs);
}

bool Rational::operator<(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator < tmpRhs.numerator);
}

bool Rational::operator>(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator > tmpRhs.numerator);
}

bool Rational::operator<=(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator <= tmpRhs.numerator);
}

bool Rational::operator>=(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator >= tmpRhs.numerator);
}

std::string Rational::toString() const {
  return numerator.toString() + "/" + denominator.toString();
}

void Rational::fixZero() {
  if (numerator == Integer(0)) {
    sign = false;
    denominator = Integer(1);
  }
}

void Rational::fixNegative() {
  if (numerator < Integer(0)) {
    numerator *= Integer(-1);
    sign = !sign;
  }
  if (denominator < Integer(0)) {
    denominator *= Integer(-1);
    sign = !sign;
  }
}

void Rational::toIrreducibleRational() {
  if (denominator == Integer(0)) {
    throw std::domain_error("Division by zero");
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
    lhs.numerator *= Integer(-1);
  }
  lhs.numerator *= (lcmVal / lhs.denominator);
  lhs.denominator = lcmVal;
  lhs.sign = false;

  if (rhs.sign) {
    rhs.numerator *= Integer(-1);
  }
  rhs.numerator *= (lcmVal / rhs.denominator);
  rhs.denominator = lcmVal;
  rhs.sign = false;
}

// Using Euclid's algorithm
static Integer gcd(const Integer &lhs, const Integer &rhs) {
  Integer tmpLhs = lhs;
  Integer tmpRhs = rhs;
  while (tmpRhs != Integer(0)) {
    Integer buff = tmpLhs % tmpRhs;
    tmpLhs = tmpRhs;
    tmpRhs = buff;
  }
  return tmpLhs;
}

// Using the formula lcm(a, b) = a * b / gcd(a, b)
static Integer lcm(const Integer &lhs, const Integer &rhs) {
  return lhs * rhs / gcd(lhs, rhs);
}

NodePtr fintamath::Rational::minimize() const {
  if (denominator == Integer(1)) {
    return std::make_shared<Integer>(numerator);
  }
  return std::make_shared<Rational>(*this);
}
