#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "fintamath/core/Constants.hpp"
#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

using namespace boost::multiprecision;

namespace fintamath {
  Real::Real() {
    impl = std::make_unique<RealImpl>();
  }

  Real::Real(const Real &rhs) : Real() {
    impl->v.assign(rhs.impl->v);
  }

  Real::Real(Real &&) noexcept = default;

  Real &Real::operator=(const Real &rhs) {
    if (this != &rhs) {
      impl = std::make_unique<RealImpl>(*rhs.impl);
    }
    return *this;
  }

  Real &Real::operator=(Real &&) noexcept = default;

  Real::~Real() = default;

  Real::Real(const RealImpl &impl) : impl(std::make_unique<RealImpl>(impl)) {
  }

  Real::Real(std::string str) : Real() {
    if (str.empty()) {
      throw InvalidInputException(*this, str);
    }

    // Validate input and remove leading zeros
    {
      size_t i = 0;
      if (str.front() == '-') {
        i++;
      }

      str.erase(i, str.find_first_not_of('0'));
      if (str.empty()) {
        str = "0";
      }

      size_t dotsNum = 0;
      for (; i < str.size(); ++i) {
        if (str[i] == '.') {
          dotsNum++;
        } else if (str[i] < '0' || str[i] > '9') {
          throw InvalidInputException(*this, str);
        }

        if (dotsNum > 1) {
          throw InvalidInputException(*this, str);
        }
      }
    }

    try {
      impl->v.assign(str);
    } catch (const std::runtime_error &) {
      throw InvalidInputException(*this, str);
    }
  }

  Real::Real(const Rational &val) : Real() {
    *this = Real(val.getInteger()) + Real(val.getNumerator()) / Real(val.getDenominator());

    if (val < 0) {
      *this = -(*this);
    }
  }

  Real::Real(const Integer &val) : Real(val.toString()) {
  }

  Real::Real(double val) : Real() {
    impl->v.assign(val);
  }

  std::string Real::toString() const {
    return impl->v.str(FINTAMATH_DEFAULT_OUTPUT_PRECISION);
  }

  std::string Real::getClassName() const {
    return "Real";
  }

  MathObjectPtr Real::simplify() const {
    if (std::string str = toString(); str.find('.') == std::string::npos) {
      return std::make_unique<Integer>(str);
    }

    return clone();
  }

  bool Real::isPrecise() const {
    return false;
  }

  Real Real::round(size_t precision) const {
    const Integer coeff = pow(10, precision);
    Real res = *this * coeff;
    res.impl->v = boost::multiprecision::round(res.impl->v);
    return res / coeff;
  }

  const std::unique_ptr<RealImpl> &Real::getImpl() const {
    return impl;
  }

  bool Real::equals(const Real &rhs) const {
    return impl->v == rhs.impl->v;
  }

  bool Real::less(const Real &rhs) const {
    return impl->v < rhs.impl->v;
  }

  bool Real::more(const Real &rhs) const {
    return impl->v > rhs.impl->v;
  }

  Real &Real::add(const Real &rhs) {
    impl->v += rhs.impl->v;
    return *this;
  }

  Real &Real::substract(const Real &rhs) {
    impl->v -= rhs.impl->v;
    return *this;
  }

  Real &Real::multiply(const Real &rhs) {
    impl->v *= rhs.impl->v;
    return *this;
  }

  Real &Real::divide(const Real &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("/", toString(), rhs.toString());
    }

    impl->v /= rhs.impl->v;
    return *this;
  }

  Real &Real::negate() {
    impl->v = -impl->v;
    return *this;
  }

  Real &Real::increase() {
    ++impl->v;
    return *this;
  }

  Real &Real::decrease() {
    --impl->v;
    return *this;
  }
}
