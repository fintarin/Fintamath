#include "fintamath/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"

namespace fintamath {

constexpr int64_t DEFAULT_PRECISION = 36;

static Integer gcd(const Integer &lhs, const Integer &rhs);
static Integer lcm(const Integer &lhs, const Integer &rhs);

Rational::Rational(const std::string &str) {
  if (str.empty()) {
    throw InvalidInputException(str);
  }

  parse(str);
}

Rational::Rational(Integer numer, Integer denom) : numerator(std::move(numer)), denominator(std::move(denom)) {
  toIrreducibleRational();
}

Rational::Rational(Integer rhs) : numerator(std::move(rhs)) {
  fixNegative();
}

Rational::Rational(int64_t rhs) : numerator(rhs) {
  fixNegative();
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

std::string Rational::toString() const {
  std::string res = signVal ? "-" : "";
  res += numerator.toString();

  if (denominator != 1) {
    res += "/" + denominator.toString();
  }

  return res;
}

std::unique_ptr<IMathObject> Rational::toMinimalObject() const {
  if (denominator == 1) {
    return signVal ? (-getInteger()).clone() : getInteger().clone();
  }
  return clone();
}

int Rational::sign() const {
  if (*this == 0) {
    return 0;
  }

  return signVal ? -1 : 1;
}

void Rational::fixZero() {
  if (numerator == 0) {
    signVal = false;
    denominator = 1;
  }
}

bool Rational::equals(const Rational &rhs) const {
  return signVal == rhs.signVal && numerator == rhs.numerator && denominator == rhs.denominator;
}

bool Rational::less(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator < tmpRhs.numerator);
}

bool Rational::more(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return (lhs.numerator > tmpRhs.numerator);
}

Rational &Rational::add(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numerator += tmpRhs.numerator;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::substract(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numerator -= tmpRhs.numerator;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::multiply(const Rational &rhs) {
  numerator *= rhs.numerator;
  denominator *= rhs.denominator;
  signVal = (!signVal || !rhs.signVal) && (signVal || rhs.signVal);
  toIrreducibleRational();
  return *this;
}

Rational &Rational::divide(const Rational &rhs) {
  numerator *= rhs.denominator;
  denominator *= rhs.numerator;
  signVal = (!signVal || !rhs.signVal) && (signVal || rhs.signVal);
  toIrreducibleRational();
  return *this;
}

Rational &Rational::negate() {
  signVal = !signVal;
  return *this;
}

void Rational::parse(const std::string &str) {
  if (str.empty() || str == ".") {
    throw InvalidInputException(str);
  }

  int64_t firstDigitNum = 0;
  int64_t firstDotNum = std::distance(str.begin(), std::find(str.begin(), str.end(), '.'));

  bool isNegative = false;
  if (str.front() == '-') {
    isNegative = true;
    firstDigitNum++;
  }

  std::string intPartStr = str.substr(size_t(firstDigitNum), size_t(firstDotNum - firstDigitNum));
  Integer intPart;

  if (!intPartStr.empty()) {
    intPart = Integer(str.substr(size_t(firstDigitNum), size_t(firstDotNum - firstDigitNum)));
  }

  if (firstDotNum + 1 < int64_t(str.size())) {
    auto numeratorStr = str.substr(size_t(firstDotNum) + 1);
    std::string denominatorStr(numeratorStr.size() + 1, '0');
    denominatorStr.front() = '1';
    numerator = Integer(numeratorStr);
    denominator = Integer(denominatorStr);
  }

  if (intPart < 0 || numerator < 0) {
    throw InvalidInputException(str);
  }

  toIrreducibleRational();
  numerator += intPart * denominator;
  if (numerator != 0) {
    signVal = isNegative;
  }
}

void Rational::fixNegative() {
  if (numerator < 0) {
    numerator *= -1;
    signVal = !signVal;
  }
  if (denominator < 0) {
    denominator *= -1;
    signVal = !signVal;
  }
}

void Rational::toIrreducibleRational() {
  if (denominator == 0) {
    throw UndefinedBinaryOperatorException("/", numerator.toString(), denominator.toString());
  }
  fixNegative();
  Integer gcdVal = gcd(numerator, denominator);
  numerator /= gcdVal;
  denominator /= gcdVal;
  fixZero();
}

void Rational::toCommonDenominators(Rational &lhs, Rational &rhs) {
  Integer lcmVal = lcm(lhs.denominator, rhs.denominator);

  if (lhs.signVal) {
    lhs.numerator *= -1;
  }
  lhs.numerator *= (lcmVal / lhs.denominator);
  lhs.denominator = lcmVal;
  lhs.signVal = false;

  if (rhs.signVal) {
    rhs.numerator *= -1;
  }
  rhs.numerator *= (lcmVal / rhs.denominator);
  rhs.denominator = lcmVal;
  rhs.signVal = false;
}

// Using Euclid's algorithm
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

// Using the formula lcm(a, b) = a * b / gcd(a, b)
static Integer lcm(const Integer &lhs, const Integer &rhs) {
  return lhs * rhs / gcd(lhs, rhs);
}

}
