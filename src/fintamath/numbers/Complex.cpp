#include "fintamath/numbers/Complex.hpp"

#include <compare>
#include <cstdint>
#include <memory>
#include <string>

#include "fintamath/core/Converter.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/INumber.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

namespace fintamath {

Complex::Complex(const Complex &rhs) : re(cast<INumber>(rhs.re->clone())), im(cast<INumber>(rhs.im->clone())) {
}

Complex &Complex::operator=(const Complex &rhs) {
  if (this != &rhs) {
    re = cast<INumber>(rhs.re->clone());
    im = cast<INumber>(rhs.im->clone());
  }

  return *this;
}

Complex::Complex(const std::string &str) {
  if (!str.empty() && str.back() == 'I') {
    im = parseNonComplexNumber(str.substr(0, str.size() - 1));
  }
  else {
    re = parseNonComplexNumber(str);
  }

  if (!re || !im) {
    throw InvalidInputException(str);
  }
}

Complex::Complex(const INumber &inReal, const INumber &inImag) {
  if (is<Complex>(inReal) || is<Complex>(inImag)) {
    throw InvalidInputException("Nested complex numbers are not allowed");
  }

  re = cast<INumber>(inReal.toMinimalObject());
  im = cast<INumber>(inImag.toMinimalObject());
}

Complex::Complex(int64_t inReal, int64_t inImag) : re(std::make_unique<Integer>(inReal)),
                                                   im(std::make_unique<Integer>(inImag)) {
}

Complex::Complex(const Integer &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(const Rational &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(const Real &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(int64_t rhs) : re(std::make_unique<Integer>(rhs)) {
}

std::string Complex::toString() const {
  std::string res;

  if (*re != Integer(0)) {
    res += re->toString();
  }

  if (*im != Integer(0)) {
    std::string imStr = im->toString();
    bool isImNeg = false;

    if (imStr.front() == '-') {
      imStr = imStr.substr(1);
      isImNeg = true;
    }

    if (*im == Integer(1) || *im == Integer(-1)) {
      imStr.clear();
    }
    else {
      imStr += " ";
    }

    if (!res.empty()) {
      res += isImNeg ? " - " : " + ";
    }
    else if (isImNeg) {
      res += "-";
    }

    res += imStr + "I";
  }

  if (res.empty()) {
    res = "0";
  }

  return res;
}

std::unique_ptr<IMathObject> Complex::toMinimalObject() const {
  if (*im == Integer(0)) {
    return re->toMinimalObject();
  }

  return clone();
}

bool Complex::isPrecise() const {
  return !is<Real>(re) && !is<Real>(im);
}

bool Complex::isComplex() const {
  return *im != Integer(0);
}

const INumber &Complex::real() const {
  return *re;
}

const INumber &Complex::imag() const {
  return *im;
}

bool Complex::equals(const Complex &rhs) const {
  return *re == *rhs.re && *im == *rhs.im;
}

std::strong_ordering Complex::compare(const Complex &rhs) const {
  if (*re == *rhs.re) {
    return *im <=> *rhs.im;
  }

  return *re <=> *rhs.re;
}

Complex &Complex::add(const Complex &rhs) {
  re = *re + *rhs.re;
  im = *im + *rhs.im;

  return *this;
}

Complex &Complex::substract(const Complex &rhs) {
  re = *re - *rhs.re;
  im = *im - *rhs.im;

  return *this;
}

// https://en.wikipedia.org/wiki/Complex_number#Multiplication_and_square
Complex &Complex::multiply(const Complex &rhs) {
  const Complex lhs = *this;

  const auto &x = *lhs.re;
  const auto &y = *lhs.im;
  const auto &u = *rhs.re;
  const auto &v = *rhs.im;

  re = *(x * u) - *(y * v);
  im = *(x * v) + *(y * u);

  return *this;
}

// https://en.wikipedia.org/wiki/Complex_number#Reciprocal_and_division
Complex &Complex::divide(const Complex &rhs) {
  const Complex lhs = *this;

  const auto &x = *lhs.re;
  const auto &y = *lhs.im;
  const auto &u = *rhs.re;
  const auto &v = *rhs.im;

  auto divisor = *(u * u) + *(v * v);

  if (is<Integer>(divisor)) {
    divisor = convert<Rational>(*divisor);
  }

  try {
    re = *(*(x * u) + *(y * v)) / *divisor;
    im = *(*(y * u) - *(x * v)) / *divisor;
  }
  catch (const UndefinedException &) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  return *this;
}

Complex &Complex::negate() {
  re = -(*re);
  im = -(*im);
  return *this;
}

std::unique_ptr<INumber> Complex::parseNonComplexNumber(const std::string &str) {
  static auto numberParser = [] {
    detail::Parser<std::unique_ptr<INumber>> parser;
    parser.registerType<Integer>();
    parser.registerType<Rational>();
    parser.registerType<Real>();
    return parser;
  }();

  return numberParser
      .parseFirst(str)
      .value_or(std::unique_ptr<INumber>{});
}

}
