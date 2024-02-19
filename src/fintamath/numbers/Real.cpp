#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <ios>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <boost/multiprecision/detail/default_ops.hpp>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberUtils.hpp"
#include "fintamath/numbers/Rational.hpp"

namespace fintamath {

using namespace detail;

constexpr unsigned precisionMultiplier = 2;
constexpr unsigned precisionDelta = 10;

Real::Real(Backend inBackend) : backend(std::move(inBackend)),
                                isNegative(backend < 0) {

  if (!isFinite()) {
    throw UndefinedException(fmt::format(R"(Undefined {})", toString()));
  }
}

Real::Real(const std::string_view str) : Real() {
  if (str.empty() || str == ".") {
    throw InvalidInputException(fmt::format(R"(Invalid {} "{}")", getTypeStatic().getName(), str));
  }

  std::string mutableStr = removeLeadingZeroes(std::string(str));

  if (mutableStr.front() == '-') {
    isNegative = true;
  }

  {
    const std::string expStr = "*10^";
    const size_t expPos = mutableStr.find(expStr);

    if (expPos != std::string::npos) {
      mutableStr.replace(expPos, expStr.length(), "e");
    }
  }

  try {
    backend.assign(mutableStr);
  }
  catch (const std::runtime_error &) {
    throw InvalidInputException(fmt::format(R"(Invalid {} "{}")", getTypeStatic().getName(), str));
  }

  if (!isFinite()) {
    throw UndefinedException(fmt::format(R"(Undefined "{}" (overflow))", str));
  }
}

Real::Real(const Rational &val) {
  *this = Real(val.numerator()) / Real(val.denominator());
}

Real::Real(const Integer &val) : backend(val.getBackend()),
                                 isNegative(val < 0) {
}

Real::Real(const int64_t val) : backend(val),
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

bool Real::isZero() const {
  return backend.is_zero();
}

const Real::Backend &Real::getBackend() const {
  return backend;
}

unsigned Real::getOutputPrecision() const {
  return outputPrecision;
}

void Real::setOutputPrecision(const unsigned precision) {
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

  const bool isResNegZero = backend.is_zero() &&
                            rhs.backend.is_zero() &&
                            (isNegative || rhs.isNegative);
  backend += rhs.backend;
  isNegative = isResNegZero || backend < 0;

  return *this;
}

Real &Real::substract(const Real &rhs) {
  updatePrecision(rhs);

  const bool isResNegZero = backend.is_zero() &&
                            rhs.backend.is_zero() &&
                            (isNegative || !rhs.isNegative);
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
  if (rhs == 0) {
    throw UndefinedException(fmt::format(R"(Undefined "{}" / "{}" (division by zero))", toString(), rhs.toString()));
  }

  updatePrecision(rhs);

  isNegative = isNegative != rhs.isNegative;
  backend /= rhs.backend;

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

void Real::validateNewPrecision(const unsigned precision) const {
  if (precision > outputPrecision) {
    throw InvalidInputException(fmt::format("Invalid precision {} (expected precision <= {})", precision, outputPrecision));
  }
}

Real::ScopedSetPrecision::ScopedSetPrecision(const unsigned precision) {
  setPrecision(precision);
}

Real::ScopedSetPrecision::~ScopedSetPrecision() {
  setPrecision(currPrecision);
}

}
