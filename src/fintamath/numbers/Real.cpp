#include "fintamath/numbers/Real.hpp"

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
    size_t firstDigitPos = 0;
    if (str.front() == '-') {
      firstDigitPos++;
    }

    str.erase(firstDigitPos, str.find_first_not_of('0'));
    if (str.empty()) {
      str = "0";
    }

    size_t dotsNum = 0;
    for (auto i : std::views::iota(firstDigitPos, str.size())) {
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
  std::string res = backend.str(outputPrecision);

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
  return outputPrecision;
}

void Real::setPrecision(uint8_t precision) {
  assert(precision <= FINTAMATH_PRECISION && precision != 0);
  outputPrecision = precision;
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
