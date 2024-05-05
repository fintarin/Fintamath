#include "fintamath/numbers/Complex.hpp"

#include <compare>
#include <cstdint>
#include <memory>
#include <string>

#include <fmt/core.h>

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

FINTAMATH_CLASS_IMPLEMENTATION(Complex)

Complex::Complex(const Complex &rhs) : re(cast<INumber>(rhs.re->clone())), im(cast<INumber>(rhs.im->clone())) {
}

Complex &Complex::operator=(const Complex &rhs) {
  if (this != &rhs) {
    re = cast<INumber>(rhs.re->clone());
    im = cast<INumber>(rhs.im->clone());
  }

  return *this;
}

Complex::Complex(const INumber &inRe, const INumber &inIm) {
  if (is<Complex>(inRe) || is<Complex>(inIm)) {
    throw InvalidInputException(fmt::format(
        R"(Nested {} numbers are not allowed)",
        getClassStatic()->getName()));
  }

  re = cast<INumber>(inRe.toMinimalObject());
  im = cast<INumber>(inIm.toMinimalObject());
}

Complex::Complex(const Integer &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(const Rational &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(const Real &rhs) : re(cast<INumber>(rhs.toMinimalObject())) {
}

Complex::Complex(const std::string &str) try {
  if (!str.empty() && str.back() == 'I') {
    im = parseNonComplexNumber(str.substr(0, str.size() - 1));
  }
  else {
    re = parseNonComplexNumber(str);
  }

  if (!re || !im) {
    throw InvalidInputException("");
  }
}
catch (const InvalidInputException &) {
  throw InvalidInputException(fmt::format(
      R"(Unable to parse {} from "{}")",
      getClassStatic()->getName(),
      str));
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

std::optional<unsigned> Complex::getPrecision() const noexcept {
  std::optional<unsigned> rePrecision = re->getPrecision();
  std::optional<unsigned> imPrecision = im->getPrecision();

  if (rePrecision && imPrecision) {
    return std::min(*rePrecision, *imPrecision);
  }

  if (rePrecision) {
    return *rePrecision;
  }

  if (imPrecision) {
    return *imPrecision;
  }

  return {};
}

bool Complex::isComplex() const noexcept {
  return *im != Integer(0);
}

const INumber &Complex::real() const noexcept {
  return *re;
}

const INumber &Complex::imag() const noexcept {
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
    throw UndefinedException(fmt::format(
        R"(div({}, {}) is undefined (division by zero))",
        toString(),
        rhs.toString()));
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
