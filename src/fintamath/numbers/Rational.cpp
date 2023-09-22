#include "fintamath/numbers/Rational.hpp"

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

Rational::Rational(const std::string &str) {
  if (str.empty()) {
    throw InvalidInputException(str);
  }

  if (str.empty() || str == ".") {
    throw InvalidInputException(str);
  }

  int64_t firstDigitNum = 0;
  int64_t firstDotNum = std::ranges::distance(str.begin(), std::ranges::find(str, '.'));

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
    numer = Integer(numeratorStr);
    denom = Integer(denominatorStr);
  }

  if (intPart < 0 || numer < 0) {
    throw InvalidInputException(str);
  }

  toIrreducibleRational();
  numer += intPart * denom;

  if (isNegative) {
    numer *= -1;
  }
}

Rational::Rational(Integer inNumer, Integer inDenom)
    : numer(std::move(inNumer)),
      denom(std::move(inDenom)) {

  toIrreducibleRational();
}

Rational::Rational(Integer rhs) : numer(std::move(rhs)) {
}

Rational::Rational(int64_t rhs) : numer(rhs) {
}

const Integer &Rational::numerator() const {
  return numer;
}

const Integer &Rational::denominator() const {
  return denom;
}

std::string Rational::toString() const {
  std::string res = numer.toString();

  if (denom != 1) {
    res += "/" + denom.toString();
  }

  return res;
}

std::unique_ptr<IMathObject> Rational::toMinimalObject() const {
  if (denom == 1) {
    return numer.clone();
  }
  return clone();
}

int Rational::sign() const {
  return numer.sign();
}

bool Rational::equals(const Rational &rhs) const {
  return numer == rhs.numer && denom == rhs.denom;
}

std::strong_ordering Rational::compare(const Rational &rhs) const {
  Rational lhs = *this;
  Rational tmpRhs = rhs;
  toCommonDenominators(lhs, tmpRhs);
  return lhs.numer <=> tmpRhs.numer;
}

Rational &Rational::add(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numer += tmpRhs.numer;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::substract(const Rational &rhs) {
  Rational tmpRhs = rhs;
  toCommonDenominators(*this, tmpRhs);
  numer -= tmpRhs.numer;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::multiply(const Rational &rhs) {
  numer *= rhs.numer;
  denom *= rhs.denom;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::divide(const Rational &rhs) {
  numer *= rhs.denom;
  denom *= rhs.numer;
  toIrreducibleRational();
  return *this;
}

Rational &Rational::negate() {
  numer = -numer;
  return *this;
}

void Rational::toIrreducibleRational() {
  if (denom == 0) {
    throw UndefinedBinaryOperatorException("/", numer.toString(), denom.toString());
  }

  if (denom < 0) {
    numer *= -1;
    denom *= -1;
  }

  Integer gcdVal = gcd(numer, denom);
  numer /= gcdVal;
  denom /= gcdVal;
}

void Rational::toCommonDenominators(Rational &lhs, Rational &rhs) {
  Integer lcmVal = lcm(lhs.denom, rhs.denom);

  lhs.numer *= (lcmVal / lhs.denom);
  lhs.denom = lcmVal;

  rhs.numer *= (lcmVal / rhs.denom);
  rhs.denom = lcmVal;
}

}
