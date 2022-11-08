#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "boost/multiprecision/cpp_int.hpp"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"

using namespace boost::multiprecision;

namespace fintamath {
  Integer::Integer() = default;

  Integer &Integer::operator=(const Integer &) = default;

  Integer &Integer::operator=(Integer &&) noexcept = default;

  Integer::Integer(const Integer &) = default;

  Integer::Integer(Integer &&) noexcept = default;

  Integer::~Integer() = default;

  Integer::Integer(std::string str) {
    if (str.empty()) {
      throw InvalidInputException(*this, str);
    }

    {
      int8_t i = 0;
      if (str.front() == '-') {
        i++;
      }
      str.erase(i, str.find_first_not_of('0'));
    }

    try {
      value = cpp_int(str);
    } catch (const std::runtime_error &) {
      throw InvalidInputException(*this, str);
    }
  }

  Integer::Integer(int64_t val) : value(val) {
  }

  Integer &Integer::operator%=(const Integer &rhs) {
    return mod(rhs);
  }

  Integer Integer::operator%(const Integer &rhs) const {
    return Integer(*this).mod(rhs);
  }

  std::string Integer::toString() const {
    return value.str();
  }

  std::string Integer::getClassName() const {
    return "Integer";
  }

  bool Integer::equals(const Integer &rhs) const {
    return value == rhs.value;
  }

  bool Integer::less(const Integer &rhs) const {
    return value < rhs.value;
  }

  bool Integer::more(const Integer &rhs) const {
    return value > rhs.value;
  }

  Integer &Integer::add(const Integer &rhs) {
    value += rhs.value;
    return *this;
  }

  Integer &Integer::substract(const Integer &rhs) {
    value -= rhs.value;
    return *this;
  }

  Integer &Integer::multiply(const Integer &rhs) {
    value *= rhs.value;
    return *this;
  }

  Integer &Integer::divide(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("/", toString(), rhs.toString());
    }

    value /= rhs.value;
    return *this;
  }

  Integer &Integer::negate() {
    value = -value;
    return *this;
  }

  Integer &Integer::increase() {
    ++value;
    return *this;
  }

  Integer &Integer::decrease() {
    --value;
    return *this;
  }

  Integer &Integer::mod(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("mod", toString(), rhs.toString());
    }

    value %= rhs.value;
    return *this;
  }

  Integer sqrt(Integer rhs) {
    if (rhs < 0) {
      throw UndefinedFunctionException("sqrt", {rhs.toString()});
    }

    rhs.value = sqrt(rhs.value);

    return rhs;
  }
}
