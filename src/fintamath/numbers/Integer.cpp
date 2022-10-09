#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include <gmpxx.h>

namespace fintamath {
  constexpr int64_t BASE = 10;

  struct IntegerImpl {
    mpz_class mpz;
  };

  static bool isIntegerStr(std::string str);

  Integer::Integer() {
    value = std::make_unique<IntegerImpl>();
  }

  Integer::Integer(const Integer &rhs) {
    value = std::make_unique<IntegerImpl>();
    *value = *rhs.value;
  }

  Integer::Integer(Integer &&rhs) noexcept : value(std::move(rhs.value)) {
  }

  Integer &Integer::operator=(const Integer &rhs) {
    if (this != &rhs) {
      value = std::make_unique<IntegerImpl>();
      *value = *rhs.value;
    }
    return *this;
  }

  Integer &Integer::operator=(Integer &&rhs) noexcept {
    if (this != &rhs) {
      value = std::move(rhs.value);
    }
    return *this;
  }

  Integer::~Integer() = default;

  Integer::Integer(const std::string &str) : Integer() {
    if (!isIntegerStr(str)) {
      throw std::invalid_argument("Invalid integer string: " + str);
    }

    value->mpz.set_str(str, BASE);
  }

  Integer::Integer(int64_t val) : Integer() {
    value->mpz = val;
  }

  size_t Integer::length() const {
    return toString().length();
  }

  Integer Integer::sqrt() const {
    if (*this < 0) {
      throw std::domain_error("Sqrt of a negative number");
    }

    Integer res;
    res.value->mpz = ::sqrt(value->mpz);
    return res;
  }

  Integer &Integer::operator%=(const Integer &rhs) {
    return mod(rhs);
  }

  Integer Integer::operator%(const Integer &rhs) const {
    return Integer(*this).mod(rhs);
  }

  std::string Integer::toString() const {
    return value->mpz.get_str(BASE);
  }

  bool Integer::equals(const Integer &rhs) const {
    return value->mpz == rhs.value->mpz;
  }

  bool Integer::less(const Integer &rhs) const {
    return value->mpz < rhs.value->mpz;
  }

  bool Integer::more(const Integer &rhs) const {
    return value->mpz > rhs.value->mpz;
  }

  Integer &Integer::add(const Integer &rhs) {
    value->mpz += rhs.value->mpz;
    return *this;
  }

  Integer &Integer::substract(const Integer &rhs) {
    value->mpz -= rhs.value->mpz;
    return *this;
  }

  Integer &Integer::multiply(const Integer &rhs) {
    value->mpz *= rhs.value->mpz;
    return *this;
  }

  Integer &Integer::divide(const Integer &rhs) {
    if (rhs == 0) {
      throw std::domain_error("Division by zero");
    }

    value->mpz /= rhs.value->mpz;
    return *this;
  }

  Integer &Integer::negate() {
    value->mpz = -value->mpz;
    return *this;
  }

  Integer &Integer::increase() {
    ++value->mpz;
    return *this;
  }

  Integer &Integer::decrease() {
    --value->mpz;
    return *this;
  }

  Integer &Integer::mod(const Integer &rhs) {
    if (rhs == 0) {
      throw std::domain_error("Modulo by zero");
    }

    value->mpz %= rhs.value->mpz;
    return *this;
  }

  static bool isIntegerStr(std::string str) {
    if (str.empty()) {
      throw std::invalid_argument("Integer invalid input");
    }

    if (str.front() == '-') {
      str = str.substr(1);
    }

    constexpr int64_t firstDigit = 0;
    constexpr int64_t lastDigit = 9;
    return std::all_of(str.begin(), str.end(),
                       [&](auto ch) { return ch - '0' >= firstDigit && ch - '0' <= lastDigit; });
  }
}
