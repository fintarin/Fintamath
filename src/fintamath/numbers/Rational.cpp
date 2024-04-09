#include "fintamath/numbers/Rational.hpp"

#include <algorithm>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Rational)

Rational::Rational(Integer rhs) : numer(std::move(rhs)) {
}

Rational::Rational(Integer inNumer, Integer inDenom)
    : numer(std::move(inNumer)),
      denom(std::move(inDenom)) {

  if (denom == 0) {
    throw UndefinedException(fmt::format(
        R"(div({}, {}) is undefined (division by zero))",
        numer.toString(),
        denom.toString()));
  }

  toIrreducibleRational();
}

Rational::Rational(const std::string_view str) try {
  if (str.empty()) {
    throw InvalidInputException("");
  }

  if (str.empty() || str == ".") {
    throw InvalidInputException("");
  }

  int64_t firstDigitNum = 0;
  const int64_t firstDotNum = std::ranges::distance(str.begin(), std::ranges::find(str, '.'));

  bool isNegative = false;
  if (str.front() == '-') {
    isNegative = true;
    firstDigitNum++;
  }

  const std::string intPartStr(str.substr(static_cast<size_t>(firstDigitNum),
                                          static_cast<size_t>(firstDotNum - firstDigitNum)));
  Integer intPart;

  if (!intPartStr.empty()) {
    intPart = Integer(str.substr(static_cast<size_t>(firstDigitNum),
                                 static_cast<size_t>(firstDotNum - firstDigitNum)));
  }

  if (firstDotNum + 1 < std::ssize(str)) {
    const std::string numeratorStr(str.substr(static_cast<size_t>(firstDotNum) + 1));
    std::string denominatorStr(numeratorStr.size() + 1, '0');
    denominatorStr.front() = '1';
    numer = Integer(numeratorStr);
    denom = Integer(denominatorStr);
  }

  if (intPart < 0 || numer < 0) {
    throw InvalidInputException("");
  }

  toIrreducibleRational();
  numer += intPart * denom;

  if (isNegative) {
    numer *= -1;
  }
}
catch (const InvalidInputException &) {
  throw InvalidInputException(fmt::format(
      R"(Unable to parse {} from "{}")",
      getClassStatic()->getName(),
      str));
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

const Integer &Rational::numerator() const noexcept {
  return numer;
}

const Integer &Rational::denominator() const noexcept {
  return denom;
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
  if (rhs == 0) {
    throw UndefinedException(fmt::format(
        R"(div({}, {}) is undefined (division by zero))",
        toString(),
        rhs.toString()));
  }

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
  if (denom < 0) {
    numer *= -1;
    denom *= -1;
  }

  const Integer gcdVal = gcd(numer, denom);
  numer /= gcdVal;
  denom /= gcdVal;
}

void Rational::toCommonDenominators(Rational &lhs, Rational &rhs) {
  const Integer lcmVal = lcm(lhs.denom, rhs.denom);

  lhs.numer *= (lcmVal / lhs.denom);
  lhs.denom = lcmVal;

  rhs.numer *= (lcmVal / rhs.denom);
  rhs.denom = lcmVal;
}

}
