#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cassert>
#include <compare>
#include <cstddef>
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

FINTAMATH_CLASS_IMPLEMENTATION(Real)

using namespace detail;

constexpr unsigned precisionMultiplier = 2;
constexpr unsigned precisionDelta = 10;

Real::Real(Backend inBackend) : backend(std::move(inBackend)) {

  if (!isFinite()) {
    throw UndefinedException(fmt::format(
        R"(Undefined backend {})",
        backend.str()));
  }
}

Real::Real(const Rational &rhs) : Real(Real(rhs.numerator()) / Real(rhs.denominator())) {}

Real::Real(const Integer &rhs) : backend(rhs.getBackend()) {}

Real::Real(const std::string_view str) {
  constexpr auto throwInvalidInputException = [](const std::string_view invalidStr) {
    throw InvalidInputException(fmt::format(
        R"(Unable to parse {} from "{}")",
        getClassStatic()->getName(),
        invalidStr));
  };

  if (str.empty() || str == ".") {
    throwInvalidInputException(str);
  }

  const std::string processedStr = [&str] {
    std::string outProcessedStr = removeLeadingZeroes(std::string(str));
    const std::string expStr = "*10^";
    const size_t expPos = outProcessedStr.find(expStr);

    if (expPos != std::string::npos) {
      outProcessedStr.replace(expPos, expStr.length(), "e");
    }

    return outProcessedStr;
  }();

  try {
    backend.assign(processedStr);
  }
  catch (const std::runtime_error &) {
    throwInvalidInputException(str);
  }

  if (!isFinite()) {
    throw UndefinedException(fmt::format(
        R"(Undefined "{}" (overflow))",
        str));
  }
}

std::string Real::toString() const noexcept {
  return toString(outputPrecision);
}

std::string Real::toString(unsigned precision) const {
  assert(precision <= outputPrecision);

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

int Real::sign() const {
  if (mpfr_signbit(backend.backend().data())) {
    return -1;
  }

  return backend.sign();
}

bool Real::isZero() const {
  return backend.is_zero();
}

bool Real::isPosZero() const {
  return isZero() && sign() >= 0;
}

bool Real::isNegZero() const {
  return isZero() && sign() < 0;
}

const Real::Backend &Real::getBackend() const noexcept {
  return backend;
}

std::optional<unsigned> Real::getPrecision() const noexcept {
  return outputPrecision;
}

void Real::setPrecision(const unsigned precision) {
  assert(precision <= outputPrecision);
  outputPrecision = precision;
}

unsigned Real::getCalculationPrecisionStatic() noexcept {
  return Backend::thread_default_precision();
}

unsigned Real::getPrecisionStatic() noexcept {
  return (getCalculationPrecisionStatic() - precisionDelta) / precisionMultiplier;
}

void Real::setPrecisionStatic(unsigned precision) {
  if (precision == 0) {
    precision++;
  }

  Backend::thread_default_precision(precision * precisionMultiplier + precisionDelta);
}

void Real::registerDefaultObject() const {
  [[maybe_unused]] static const unsigned defaultPrecision = [] {
    constexpr unsigned precision = 20;
    Real::setPrecisionStatic(precision);
    return precision;
  }();
}

bool Real::equals(const Real &rhs) const {
  return backend == rhs.backend && sign() == rhs.sign();
}

std::strong_ordering Real::compare(const Real &rhs) const {
  if (sign() != rhs.sign()) {
    return sign() <=> rhs.sign();
  }

  return backend.compare(rhs.backend) <=> 0;
}

Real &Real::add(const Real &rhs) {
  updatePrecision(rhs);

  bool isResultNegZero = isZero() &&
                         rhs.isZero() &&
                         (sign() < 0 || rhs.sign() < 0);

  if (!isResultNegZero) {
    backend += rhs.backend;
  }
  else {
    backend = 0;
    backend = -backend;
  }

  return *this;
}

Real &Real::substract(const Real &rhs) {
  updatePrecision(rhs);

  bool isResultNegZero = isZero() &&
                         rhs.isZero() &&
                         (sign() < 0 || rhs.sign() >= 0);

  if (!isResultNegZero) {
    backend -= rhs.backend;
  }
  else {
    backend = 0;
    backend = -backend;
  }

  return *this;
}

Real &Real::multiply(const Real &rhs) {
  updatePrecision(rhs);
  backend *= rhs.backend;
  return *this;
}

Real &Real::divide(const Real &rhs) {
  if (rhs.isZero()) {
    throw UndefinedException(fmt::format(
        R"(div({}, {}) is undefined (division by zero))",
        toString(),
        rhs.toString()));
  }

  updatePrecision(rhs);
  backend /= rhs.backend;
  return *this;
}

Real &Real::negate() {
  backend = -backend;
  return *this;
}

bool Real::isFinite() const {
  return boost::math::isfinite(backend);
}

void Real::updatePrecision(const Real &rhs) {
  outputPrecision = std::min(outputPrecision, rhs.outputPrecision);
}

Real::ScopedSetPrecision::ScopedSetPrecision(const unsigned precision) {
  setPrecisionStatic(precision);
}

Real::ScopedSetPrecision::~ScopedSetPrecision() {
  setPrecisionStatic(currPrecision);
}

}
