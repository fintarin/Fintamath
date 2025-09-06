#include "fintamath/numbers/Rational.hpp"

#include <algorithm>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/core/Converter.hpp"
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
      denom.toString()
    ));
  }

  toIrreducibleRational();
}

Rational::Rational(const std::string_view str) {
  constexpr auto throwInvalidInputException = [](const std::string_view invalidStr) {
    throw InvalidInputException(fmt::format(
      R"(Unable to parse {} from "{}")",
      getClassStatic()->getName(),
      invalidStr
    ));
  };

  if (str.empty()) {
    throwInvalidInputException(str);
  }

  if (str.empty() || str == ".") {
    throwInvalidInputException(str);
  }

  int64_t firstDigitIndex = 0;
  const int64_t firstDotIndex = std::ranges::distance(str.begin(), std::ranges::find(str, '.'));

  bool isNegative = false;
  if (str.front() == '-') {
    isNegative = true;
    firstDigitIndex++;
  }

  const std::string intPartStr(str.substr(
    static_cast<size_t>(firstDigitIndex),
    static_cast<size_t>(firstDotIndex - firstDigitIndex)
  ));
  Integer intPart;

  try {
    if (!intPartStr.empty()) {
      intPart = Integer(str.substr(
        static_cast<size_t>(firstDigitIndex),
        static_cast<size_t>(firstDotIndex - firstDigitIndex)
      ));
    }

    if (firstDotIndex + 1 < std::ssize(str)) {
      const std::string numeratorStr(str.substr(static_cast<size_t>(firstDotIndex) + 1));
      std::string denominatorStr(numeratorStr.size() + 1, '0');
      denominatorStr.front() = '1';
      numer = Integer(numeratorStr);
      denom = Integer(denominatorStr);
    }
  }
  catch (const InvalidInputException &) {
    throwInvalidInputException(str);
  }

  if (intPart < 0 || numer < 0) {
    throwInvalidInputException(str);
  }

  toIrreducibleRational();
  numer += intPart * denom;

  if (isNegative) {
    numer *= -1;
  }
}

std::string Rational::toString() const noexcept {
  std::string res = numer.toString();

  if (denom != 1) {
    res += "/" + denom.toString();
  }

  return res;
}

Shared<IMathObject> Rational::unwrapp() const noexcept {
  if (denom == 1) {
    return numer.clone();
  }

  return {};
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

void Rational::registerDefaultObject() const noexcept {
  using detail::Converter;

  Converter::add<Rational, Integer>();
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
      rhs.toString()
    ));
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
