#include "fintamath/numbers/Real.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/IntegerFunctions.hpp"
#include "fintamath/numbers/NumberUtils.hpp"

namespace fintamath {

const unsigned precisionMultiplier = 2;
const unsigned precisionDelta = 10;

Real::Real(Backend inBackend) : backend(std::move(inBackend)),
                                isNegative(backend < 0) {

  if (!isFinite()) {
    throw UndefinedException(backend.str());
  }
}

Real::Real(std::string str) : Real() {
  if (str.empty() || str == ".") {
    throw InvalidInputException(str);
  }

  str = removeLeadingZeroes(std::move(str));

  if (str.front() == '-') {
    isNegative = true;
  }

  {
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

  if (!isFinite()) {
    throw UndefinedException(str);
  }
}

Real::Real(const Rational &val) {
  *this = Real(val.numerator()) / Real(val.denominator());
}

Real::Real(const Integer &val) : backend(val.getBackend()),
                                 isNegative(val < 0) {
}

Real::Real(int64_t val) : backend(val),
                          isNegative(val < 0) {
}

std::string Real::toString() const {
  std::string res = toString(outputPrecision);

  if (isNegative && res.front() != '-') {
    res.insert(res.begin(), '-');
  }

  return res;
}

std::string Real::toString(unsigned precision) const {
  validateNewPrecision(precision);

  if (precision == 0) {
    precision++;
  }

  std::string str = backend.str(static_cast<std::streamsize>(precision));
  size_t expPos = str.find('e');

  if (expPos != std::string::npos) {
    size_t expNextPos = expPos + 1;

    if (str[expNextPos] == '+') {
      str.erase(expNextPos, 1);
    }
    else {
      expNextPos++;
    }

    if (str[expNextPos] == '0') {
      str.erase(expNextPos, 1);
    }

    str.replace(expPos, 1, "*10^");
  }
  else {
    expPos = str.size();
  }

  if (str.find('.') == std::string::npos) {
    str.insert(expPos, ".0");
  }

  if (str.ends_with("^1")) {
    str.erase(str.size() - 2, 2);
  }

  return str;
}

bool Real::isPrecise() const {
  return false;
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

unsigned Real::getOutputPrecision() const {
  return outputPrecision;
}

void Real::setOutputPrecision(unsigned precision) {
  validateNewPrecision(precision);
  outputPrecision = precision;
}

unsigned Real::getCalculationPrecision() {
  return Backend::thread_default_precision();
}

unsigned Real::getPrecision() {
  return (getCalculationPrecision() - precisionDelta) / precisionMultiplier;
}

void Real::setPrecision(unsigned precision) {
  if (precision == 0) {
    precision++;
  }

  Backend::thread_default_precision(precision * precisionMultiplier + precisionDelta);
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
  updatePrecision(rhs);

  bool isResNegZero = backend.is_zero() && rhs.backend.is_zero() && (isNegative || rhs.isNegative);
  backend += rhs.backend;
  isNegative = isResNegZero || backend < 0;

  return *this;
}

Real &Real::substract(const Real &rhs) {
  updatePrecision(rhs);

  bool isResNegZero = backend.is_zero() && rhs.backend.is_zero() && (isNegative || !rhs.isNegative);
  backend -= rhs.backend;
  isNegative = isResNegZero || backend < 0;

  return *this;
}

Real &Real::multiply(const Real &rhs) {
  updatePrecision(rhs);

  isNegative = isNegative != rhs.isNegative;
  backend *= rhs.backend;

  return *this;
}

Real &Real::divide(const Real &rhs) {
  updatePrecision(rhs);

  isNegative = isNegative != rhs.isNegative;
  backend /= rhs.backend;

  if (!isFinite()) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  return *this;
}

Real &Real::negate() {
  isNegative = !isNegative;
  backend = -backend;
  return *this;
}

bool Real::isFinite() const {
  return boost::math::isfinite(backend);
}

void Real::updatePrecision(const Real &rhs) {
  outputPrecision = std::min(outputPrecision, rhs.outputPrecision);
}

void Real::validateNewPrecision(unsigned precision) const {
  if (precision > outputPrecision) {
    // TODO: use std::format
    throw InvalidInputException("Precision must be less than or equal to " +
                                std::to_string(outputPrecision));
  }
}

Real::ScopedSetPrecision::ScopedSetPrecision(unsigned precision) {
  Real::setPrecision(precision);
}

Real::ScopedSetPrecision::~ScopedSetPrecision() {
  Real::setPrecision(currPrecision);
}

}
