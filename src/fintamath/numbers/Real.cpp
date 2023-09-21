#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

using namespace boost::multiprecision;

namespace fintamath {

Real::Real() = default;

Real::Real(const Real &rhs) = default;

Real::Real(Real &&rhs) noexcept = default;

Real &Real::operator=(const Real &rhs) = default;

Real &Real::operator=(Real &&rhs) noexcept = default;

Real::~Real() = default;

Real::Real(cpp_dec_float_100 inBackend) : backend(std::move(inBackend)) {
}

Real::Real(std::string str) : Real() {
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

  backend.assign(str);
}

Real::Real(const Rational &val) {
  *this = Real(val.numerator()) / Real(val.denominator());
}

Real::Real(const Integer &val) : backend(val.getBackend()) {
}

Real::Real(double val) : backend(val) {
}

std::string Real::toString() const {
  std::stringstream ss;
  ss.precision(ouputPrecision);
  ss << backend;
  std::string res = ss.str();

  size_t expPos = res.find('e');

  if (expPos != std::string::npos) {
    res.replace(expPos, 1, "*10^");

    if (size_t plusPos = res.find('+'); plusPos != std::string::npos) {
      res.replace(plusPos, 1, "");
    }

    if (size_t negZeroPos = res.find("-0"); negZeroPos != std::string::npos) {
      res.replace(negZeroPos + 1, 1, "");
    }
  }
  else {
    expPos = res.length();
  }

  if (res.find('.') == std::string::npos) {
    res.insert(expPos, ".0");
  }

  return res;
}

bool Real::isPrecise() const {
  return false;
}

Real Real::precise(uint8_t precision) const {
  assert(precision <= FINTAMATH_PRECISION);
  Real res = *this;
  res.ouputPrecision = precision;
  return res;
}

int Real::sign() const {
  return backend.sign();
}

const cpp_dec_float_100 &Real::getBackend() const {
  return backend;
}

bool Real::equals(const Real &rhs) const {
  return backend == rhs.backend;
}

std::strong_ordering Real::compare(const Real &rhs) const {
  return backend.compare(rhs.backend) <=> 0;
}

Real &Real::add(const Real &rhs) {
  backend += rhs.backend;
  return *this;
}

Real &Real::substract(const Real &rhs) {
  backend -= rhs.backend;
  return *this;
}

Real &Real::multiply(const Real &rhs) {
  backend *= rhs.backend;
  return *this;
}

Real &Real::divide(const Real &rhs) {
  backend /= rhs.backend;

  if (!backend.backend().isfinite()) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  return *this;
}

Real &Real::negate() {
  backend = -backend;
  return *this;
}
}
