#include "fintamath/numbers/Rational.hpp"

#include <algorithm>
#include <stdexcept>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"

namespace fintamath {
  constexpr int64_t DEFAULT_PRECISION = 36;

  static Integer gcd(const Integer &lhs, const Integer &rhs);
  static Integer lcm(const Integer &lhs, const Integer &rhs);

  Rational::Rational(const std::string &str) {
    if (str.empty()) {
      throw InvalidInputException(*this, str);
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

  Rational Rational::round(int64_t precision) const {
    Rational res(toString(precision));
    res.precise = false;
    return res;
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

  std::string Rational::toString(int64_t precision) const {
    constexpr int64_t base = 10;
    constexpr int64_t roundUp = 5;

    std::string precisionStr(size_t(precision) + 2, '0');
    precisionStr.front() = '1';

    Integer val = numerator * Integer(precisionStr) / denominator;
    if (val % base >= roundUp) {
      val += base;
    }
    val /= base;

    std::string strVal = val.toString();
    if (strVal.size() <= size_t(precision)) {
      strVal.insert(strVal.begin(), size_t(precision) + 1 - strVal.size(), '0');
    }
    strVal.insert(strVal.end() - precision, '.');

    while (!strVal.empty() && strVal.back() == '0') {
      strVal.pop_back();
    }
    if (strVal.back() == '.') {
      strVal.pop_back();
    }

    if (sign) {
      strVal.insert(strVal.begin(), '-');
    }

    return strVal;
  }

  std::string Rational::toString() const {
    if (!precise) {
      return toString(DEFAULT_PRECISION);
    }
    std::string res = sign ? "-" : "";
    res += numerator.toString();
    if (denominator != 1) {
      res += "/" + denominator.toString();
    }
    return res;
  }

  std::string Rational::getClassName() const {
    return "Rational";
  }

  MathObjectPtr Rational::simplify() const {
    if (denominator == 1) {
      return sign ? (-getInteger()).clone() : getInteger().clone();
    }
    return clone();
  }

  void Rational::fixZero() {
    if (numerator == 0) {
      sign = false;
      denominator = 1;
    }
  }

  bool Rational::equals(const Rational &rhs) const {
    return sign == rhs.sign && numerator == rhs.numerator && denominator == rhs.denominator && precise == rhs.precise;
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
    solvePrecision(rhs);
    return *this;
  }

  Rational &Rational::substract(const Rational &rhs) {
    Rational tmpRhs = rhs;
    toCommonDenominators(*this, tmpRhs);
    numerator -= tmpRhs.numerator;
    toIrreducibleRational();
    solvePrecision(rhs);
    return *this;
  }

  Rational &Rational::multiply(const Rational &rhs) {
    numerator *= rhs.numerator;
    denominator *= rhs.denominator;
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
    toIrreducibleRational();
    solvePrecision(rhs);
    return *this;
  }

  Rational &Rational::divide(const Rational &rhs) {
    numerator *= rhs.denominator;
    denominator *= rhs.numerator;
    sign = !((sign && rhs.sign) || (!sign && !rhs.sign));
    toIrreducibleRational();
    solvePrecision(rhs);
    return *this;
  }

  Rational &Rational::negate() {
    sign = !sign;
    return *this;
  }

  Rational &Rational::increase() {
    return *this += 1;
  }

  Rational &Rational::decrease() {
    return *this -= 1;
  }

  void Rational::parse(const std::string &str) {
    int64_t firstDigitNum = 0;
    int64_t firstDotNum = std::distance(str.begin(), std::find(str.begin(), str.end(), '.'));

    bool isNegative = false;
    if (str.front() == '-') {
      isNegative = true;
      firstDigitNum++;
    }

    Integer intPart;
    try {
      intPart = Integer(str.substr(size_t(firstDigitNum), size_t(firstDotNum - firstDigitNum)));
    } catch (const std::invalid_argument &) {
      throw InvalidInputException(*this, str);
    }

    if (size_t(firstDotNum) != str.size()) {
      try {
        auto numeratorStr = str.substr(size_t(firstDotNum) + 1);
        std::string denominatorStr(numeratorStr.size() + 1, '0');
        denominatorStr.front() = '1';
        numerator = Integer(numeratorStr);
        denominator = Integer(denominatorStr);
      } catch (const std::invalid_argument &) {
        throw InvalidInputException(*this, str);
      }
    }

    if (intPart < 0 || numerator < 0) {
      throw InvalidInputException(*this, str);
    }

    toIrreducibleRational();
    numerator += intPart * denominator;
    if (numerator != 0) {
      sign = isNegative;
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
      throw UndefinedBinaryOpearatorException("/", numerator.toString(), denominator.toString());
    }
    fixNegative();
    Integer gcdVal = gcd(numerator, denominator);
    numerator /= gcdVal;
    denominator /= gcdVal;
    fixZero();
  }

  void Rational::solvePrecision(const Rational &rhs) {
    precise = precise && rhs.precise;
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
