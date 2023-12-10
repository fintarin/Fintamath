#include "fintamath/numbers/Real.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"

namespace fintamath {

Real::Real(Backend inBackend) : backend(std::move(inBackend)),
                                isNegative(backend < 0) {

  if (!isValid()) {
    throw UndefinedException(backend.str());
  }
}

Real::Real(std::string str) : Real() {
  if (str.empty() || str == ".") {
    throw InvalidInputException(str);
  }

  {
    size_t firstDigitPos = 0;
    if (str.front() == '-') {
      firstDigitPos++;
      isNegative = true;
    }

    str.erase(firstDigitPos, str.find_first_not_of('0'));
    if (str.empty()) {
      str = "0";
    }

    std::string expStr = "*10^";
    size_t expPos = str.find(expStr);
    if (expPos != std::string::npos) {
      str.replace(expPos, expStr.length(), "e");
    }
  }

  try {
    backend.assign(str);
  }
  catch (const std::runtime_error &) {
    throw InvalidInputException(str);
  }
}

Real::Real(const Rational &val) {
  *this = Real(val.numerator()) / Real(val.denominator());
}

Real::Real(const Integer &val) : backend(val.getBackend()),
                                 isNegative(val < 0) {
}

Real::Real(double val) : backend(val),
                         isNegative(val < 0) {
}

std::string Real::toString() const {
  std::string res = toString(precision);

  if (isNegative && res.front() != '-') {
    res.insert(res.begin(), '-');
  }

  return res;
}

std::string Real::toString(uint8_t inPrecision) const {
  assert(inPrecision <= FINTAMATH_PRECISION && inPrecision != 0);

  std::string res = backend.str(inPrecision);

  size_t expPos = res.find('e');

  if (expPos != std::string::npos) {
    {
      size_t expNextPos = expPos + 1;

      if (res[expNextPos] == '+') {
        res.erase(expNextPos, 1);
      }
      else {
        expNextPos++;
      }

      if (res[expNextPos] == '0') {
        res.erase(expNextPos, 1);
      }
    }

    res.replace(expPos, 1, "*10^");
  }
  else {
    expPos = res.size();
  }

  if (res.find('.') == std::string::npos) {
    res.insert(expPos, ".0");
  }

  if (res.ends_with("^1")) {
    res.erase(res.size() - 2, 2);
  }

  return res;
}

bool Real::isPrecise() const {
  return false;
}

uint8_t Real::getPrecision() const {
  return precision;
}

void Real::setPrecision(uint8_t inPrecision) {
  assert(inPrecision <= FINTAMATH_PRECISION && inPrecision != 0);
  backend.precision(inPrecision);
  precision = inPrecision;
}

int Real::sign() const {
  if (isNegative) {
    return -1;
  }

  return backend.sign();
}

const Real::Backend &Real::getBackend() const {
  return backend;
}

bool Real::equals(const Real &rhs) const {
  return backend == rhs.backend && isNegative == rhs.isNegative;
}

std::strong_ordering Real::compare(const Real &rhs) const {
  if (isNegative && !rhs.isNegative) {
    return std::strong_ordering::less;
  }

  if (!isNegative && rhs.isNegative) {
    return std::strong_ordering::greater;
  }

  return backend.compare(rhs.backend) <=> 0;
}

Real &Real::add(const Real &rhs) {
  bool isResNegZero = backend.is_zero() && rhs.backend.is_zero() && (isNegative || rhs.isNegative);
  backend += rhs.backend;
  isNegative = isResNegZero || backend < 0;
  return *this;
}

Real &Real::substract(const Real &rhs) {
  bool isResNegZero = backend.is_zero() && rhs.backend.is_zero() && (isNegative || !rhs.isNegative);
  backend -= rhs.backend;
  isNegative = isResNegZero || backend < 0;
  return *this;
}

Real &Real::multiply(const Real &rhs) {
  isNegative = isNegative != rhs.isNegative;
  backend *= rhs.backend;
  return *this;
}

Real &Real::divide(const Real &rhs) {
  isNegative = isNegative != rhs.isNegative;
  backend /= rhs.backend;

  if (!isValid()) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  return *this;
}

Real &Real::negate() {
  isNegative = !isNegative;
  backend = -backend;
  return *this;
}

bool Real::isValid() const {
  return boost::math::isfinite(backend);
}

}
