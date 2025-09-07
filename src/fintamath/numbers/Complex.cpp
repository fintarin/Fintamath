#include "fintamath/numbers/Complex.hpp"

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

namespace {

template <typename T>
SharedRef<INumber> unwrappOrClone(const T &num) {
  if (auto unwrapped = num.unwrapp()) {
    return castChecked<INumber>(unwrapped.toRef());
  }

  return castChecked<INumber>(SharedRef<IMathObject>(num.clone()));
}

template <typename T>
SharedRef<INumber> unwrappOrReturn(const T &num) {
  if (auto unwrapped = num->unwrapp()) {
    return castChecked<INumber>(unwrapped.toRef());
  }

  return num;
}

}

Complex::Complex()
    : re(Integer::getZero()),
      im(Integer::getZero()) {}

Complex::Complex(const Integer &rhs)
    : re(unwrappOrClone(rhs)),
      im(Integer::getZero()) {}

Complex::Complex(const Rational &rhs)
    : re(unwrappOrClone(rhs)),
      im(Integer::getZero()) {}

Complex::Complex(const Real &rhs)
    : re(unwrappOrClone(rhs)),
      im(Integer::getZero()) {
}

Complex::Complex(const INumber &inReal, const INumber &inImage)
    : re(unwrappOrClone(inReal)),
      im(unwrappOrClone(inImage)) {

  if (is<Complex>(inReal) || is<Complex>(inImage)) {
    throw InvalidInputException(fmt::format(
      R"(Nested {} numbers are not allowed)",
      getClassStatic()->getName()
    ));
  }
}

Complex::Complex(const SharedRef<INumber> &inReal, const SharedRef<INumber> &inImage)
    : re(unwrappOrReturn(inReal)),
      im(unwrappOrReturn(inImage)) {

  if (auto reUnwrapped = re->unwrapp()) {
    re = castChecked<INumber>(reUnwrapped.toRef());
  }
  if (auto imUnwrapped = im->unwrapp()) {
    im = castChecked<INumber>(imUnwrapped.toRef());
  }
}

Complex::Complex(const std::string &str)
    : re(Integer::getZero()),
      im(Integer::getZero()) {

  try {
    if (!str.empty() && str.back() == 'I') {
      re = Integer::getZero();
      im = parseNonComplexNumber(str.substr(0, str.size() - 1));
    }
    else {
      re = parseNonComplexNumber(str);
      im = Integer::getZero();
    }
  }
  catch (const InvalidInputException &) {
    throw InvalidInputException(fmt::format(
      R"(Unable to parse {} from "{}")",
      getClassStatic()->getName(),
      str
    ));
  }
}

std::string Complex::toString() const noexcept {
  const auto *reInt = cast<Integer>(re.get());
  const auto *imInt = cast<Integer>(im.get());

  std::string res;

  if (!reInt || !reInt->isZero()) {
    res += re->toString();
  }

  if (!imInt || !imInt->isZero()) {
    std::string imStr = im->toString();
    bool isImNeg = false;

    if (imStr.front() == '-') {
      imStr = imStr.substr(1);
      isImNeg = true;
    }

    if (imInt && (*imInt == 1 || *imInt == -1)) {
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

SharedPtr<IMathObject> Complex::unwrapp() const noexcept {
  if (!isComplex()) {
    return re;
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
    return rePrecision;
  }

  if (imPrecision) {
    return imPrecision;
  }

  return {};
}

bool Complex::isZero() const noexcept {
  return re->isZero() && im->isZero();
}

bool Complex::isComplex() const noexcept {
  const auto *imInt = cast<Integer>(im.get());
  return !imInt->isZero();
}

const SharedRef<INumber> &Complex::real() const noexcept {
  return re;
}

const SharedRef<INumber> &Complex::imag() const noexcept {
  return im;
}

bool Complex::equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept {
  return Super::equals(self, rhs);
}

bool Complex::equals(const Complex &rhs) const noexcept {
  using fintamath::equals;
  return equals(re, rhs.re) && equals(im, rhs.im);
}

Complex &Complex::add(const Complex &rhs) {
  using fintamath::add;

  re = add(re, rhs.re);
  im = add(im, rhs.im);

  return *this;
}

Complex &Complex::sub(const Complex &rhs) {
  using fintamath::sub;

  re = sub(re, rhs.re);
  im = sub(im, rhs.im);

  return *this;
}

// https://en.wikipedia.org/wiki/Complex_number#Multiplication_and_square
Complex &Complex::mul(const Complex &rhs) {
  using fintamath::add;
  using fintamath::mul;
  using fintamath::sub;

  Complex lhs = *this;

  const auto &x = lhs.re;
  const auto &y = lhs.im;
  const auto &u = rhs.re;
  const auto &v = rhs.im;

  re = sub(mul(x, u), mul(y, v));
  im = add(mul(x, v), mul(y, u));

  return *this;
}

// https://en.wikipedia.org/wiki/Complex_number#Reciprocal_and_division
Complex &Complex::div(const Complex &rhs) {
  using fintamath::add;
  using fintamath::div;
  using fintamath::mul;
  using fintamath::sub;

  Complex lhs = *this;

  const auto &x = lhs.re;
  const auto &y = lhs.im;
  const auto &u = rhs.re;
  const auto &v = rhs.im;

  re = add(mul(x, u), mul(y, v));
  im = sub(mul(y, u), mul(x, v));

  auto divisor = add(mul(u, u), mul(v, v));

  try {
    re = div(re, divisor);
    im = div(im, divisor);
  }
  catch (const UndefinedException &) {
    throw UndefinedException(fmt::format(
      R"(div({}, {}) is undefined (division by zero))",
      lhs.toString(),
      rhs.toString()
    ));
  }

  return *this;
}

Complex &Complex::neg() {
  using fintamath::neg;

  re = neg(re);
  im = neg(im);

  return *this;
}

SharedRef<INumber> Complex::parseNonComplexNumber(const std::string &str) {
  if (str.find('.') != std::string::npos) {
    return unwrappOrReturn(makeShared<Rational>(str));
  }
  return unwrappOrReturn(makeShared<Integer>(str));
}
}
