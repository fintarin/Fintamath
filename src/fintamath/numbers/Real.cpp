#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

using namespace boost::multiprecision;

namespace fintamath {

static RealImpl initDelta() {
  const RealImpl::Backend delta = pow(RealImpl::Backend(10), -FINTAMATH_ROUND_PRECISION);
  return delta;
}

const RealImpl Real::DELTA = initDelta();

Real::Real() {
  impl = make_unique<RealImpl>();
}

Real::Real(const Real &rhs) : Real() {
  impl->v.assign(rhs.impl->v);
  ouputPrecision = rhs.ouputPrecision; // NOLINT
}

Real::Real(Real &&) noexcept = default;

Real &Real::operator=(const Real &rhs) {
  if (this != &rhs) {
    impl = make_unique<RealImpl>(*rhs.impl);
    ouputPrecision = rhs.ouputPrecision;
  }
  return *this;
}

Real &Real::operator=(Real &&) noexcept = default;

Real::~Real() = default;

Real::Real(const RealImpl &impl) : impl(make_unique<RealImpl>(impl)) {
}

Real::Real(string str) : Real() {
  if (str.empty() || str == ".") {
    throw InvalidInputException(str);
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
      }
      else if (str[i] < '0' || str[i] > '9') {
        throw InvalidInputException(str);
      }

      if (dotsNum > 1) {
        throw InvalidInputException(str);
      }
    }
  }

  impl->v.assign(str);
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

string Real::toString() const {
  std::stringstream ss;
  ss.precision(ouputPrecision);
  ss << impl->v;
  string res = ss.str();

  if (size_t ePos = res.find('e'); ePos != string::npos) {
    res.replace(ePos, 1, "*10^");

    if (size_t plusPos = res.find('+'); plusPos != string::npos) {
      res.replace(plusPos, 1, "");
    }
  }

  return res;
}

unique_ptr<IMathObject> Real::toMinimalObject() const {
  if (impl->v.backend().isfinite()) {
    if (string str = toString(); str.find('.') == string::npos && str.find('*') == string::npos) {
      return make_unique<Integer>(str);
    }
  }

  return clone();
}

bool Real::isPrecise() const {
  return false;
}

Real Real::precise(uint8_t precision) const {
  assert(precision <= FINTAMATH_ROUND_PRECISION);
  Real res = *this;
  res.ouputPrecision = precision;
  return res;
}

int Real::sign() const {
  return impl->v.sign();
}

bool Real::isNearZero() const {
  return abs(impl->v) < DELTA;
}

const unique_ptr<RealImpl> &Real::getImpl() const {
  return impl;
}

bool Real::equals(const Real &rhs) const {
  return (*this - rhs).isNearZero();
}

bool Real::less(const Real &rhs) const {
  if (*this == rhs) {
    return false;
  }
  return impl->v < rhs.impl->v;
}

bool Real::more(const Real &rhs) const {
  if (*this == rhs) {
    return false;
  }
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
  if (rhs.isNearZero()) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  impl->v /= rhs.impl->v;
  return *this;
}

Real &Real::negate() {
  impl->v = -impl->v;
  return *this;
}

}
