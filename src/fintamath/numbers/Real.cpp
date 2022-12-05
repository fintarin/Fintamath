#include "fintamath/numbers/Real.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "boost/multiprecision/cpp_dec_float.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace boost::multiprecision;

namespace fintamath {
  struct RealImpl {
    cpp_dec_float_100 v;
  };

  Real::Real() {
    value = std::make_unique<RealImpl>();
  }

  Real::Real(const Real &rhs) : Real() {
    value->v.assign(rhs.value->v);
  }

  Real::Real(Real &&) noexcept = default;

  Real &Real::operator=(const Real &rhs) {
    if (this != &rhs) {
      value = std::make_unique<RealImpl>(*rhs.value);
    }
    return *this;
  }

  Real &Real::operator=(Real &&) noexcept = default;

  Real::~Real() = default;

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
      value->v.assign(str);
    } catch (const std::runtime_error &) {
      throw InvalidInputException(*this, str);
    }
  }

  Real::Real(const Rational &val) : Real() {
    *this = Real(val.getInteger()) + Real(val.getNumerator()) / Real(val.getDenominator());
  }

  Real::Real(const Integer &val) : Real(val.toString()) {
  }

  Real::Real(double val) : Real() {
    value->v.assign(val);
  }

  std::string Real::toString() const {
    return value->v.str();
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

  bool Real::equals(const Real &rhs) const {
    return value->v == rhs.value->v;
  }

  bool Real::less(const Real &rhs) const {
    return value->v < rhs.value->v;
  }

  bool Real::more(const Real &rhs) const {
    return value->v > rhs.value->v;
  }

  Real &Real::add(const Real &rhs) {
    value->v += rhs.value->v;
    return *this;
  }

  Real &Real::substract(const Real &rhs) {
    value->v -= rhs.value->v;
    return *this;
  }

  Real &Real::multiply(const Real &rhs) {
    value->v *= rhs.value->v;
    return *this;
  }

  Real &Real::divide(const Real &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("/", toString(), rhs.toString());
    }

    value->v /= rhs.value->v;
    return *this;
  }

  Real &Real::negate() {
    value->v = -value->v;
    return *this;
  }

  Real &Real::increase() {
    ++value->v;
    return *this;
  }

  Real &Real::decrease() {
    --value->v;
    return *this;
  }

  Real sqrt(Real rhs) {
    if (rhs < 0) {
      throw UndefinedFunctionException("sqrt", {rhs.toString()});
    }

    rhs.value->v = sqrt(rhs.value->v);

    return rhs;
  }
}
