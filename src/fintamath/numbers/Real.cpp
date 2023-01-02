#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
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
  impl = std::make_unique<RealImpl>();
}

Real::Real(const Real &rhs) : Real() {
  impl->v.assign(rhs.impl->v);
  ouputPrecision = rhs.ouputPrecision; // NOLINT
}

Real::Real(Real &&) noexcept = default;

Real &Real::operator=(const Real &rhs) {
  if (this != &rhs) {
    impl = std::make_unique<RealImpl>(*rhs.impl);
    ouputPrecision = rhs.ouputPrecision;
  }
  return *this;
}

Real &Real::operator=(Real &&) noexcept = default;

Real::~Real() = default;

Real::Real(const RealImpl &impl) : impl(std::make_unique<RealImpl>(impl)) {
}

Real::Real(std::string str) : Real() {
  if (str.empty()) {
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
      } else if (str[i] < '0' || str[i] > '9') {
        throw InvalidInputException(str);
      }

      if (dotsNum > 1) {
        throw InvalidInputException(str);
      }
    }
  }

  try {
    impl->v.assign(str);
  } catch (const std::runtime_error &) {
    throw InvalidInputException(str);
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
  std::stringstream ss;
  ss.precision(ouputPrecision);
  ss << impl->v;
  std::string res = ss.str();

  if (size_t ePos = res.find('e'); ePos != std::string::npos) {
    res.replace(ePos, 1, "*10^");

    if (size_t plusPos = res.find('+'); plusPos != std::string::npos) {
      res.replace(plusPos, 1, "");
    }
  }

  return res;
}

MathObjectPtr Real::simplify() const {
  if (impl->v.backend().isfinite()) {
    if (std::string str = toString(); str.find('.') == std::string::npos && str.find('*') == std::string::npos) {
      return std::make_unique<Integer>(str);
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

const std::unique_ptr<RealImpl> &Real::getImpl() const {
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
