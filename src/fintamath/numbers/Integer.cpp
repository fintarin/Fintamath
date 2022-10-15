#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "gmp/mini-gmp.h"

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(disable : 4244)
#endif

namespace fintamath {
  constexpr int64_t BASE = 10;

  struct IntegerImpl {
    mpz_t mpz{};

    IntegerImpl() {
      mpz_init_set_ui(mpz, 0);
    }

    IntegerImpl(const IntegerImpl &rhs) {
      mpz_set(mpz, rhs.mpz);
    }

    IntegerImpl(IntegerImpl &&rhs) noexcept = delete;

    IntegerImpl &operator=(const IntegerImpl &rhs) {
      if (this != &rhs) {
        mpz_set(mpz, rhs.mpz);
      }
      return *this;
    }

    IntegerImpl &operator=(IntegerImpl &&rhs) = delete;

    ~IntegerImpl() {
      mpz_clear(mpz);
    }
  };

  static bool isIntegerStr(std::string str);

  Integer::Integer() {
    value = std::make_unique<IntegerImpl>();
  }

  Integer::Integer(const Integer &rhs) {
    value = std::make_unique<IntegerImpl>(*rhs.value);
  }

  Integer::Integer(Integer &&rhs) noexcept : value(std::move(rhs.value)) {
  }

  Integer &Integer::operator=(const Integer &rhs) {
    if (this != &rhs) {
      value = std::make_unique<IntegerImpl>(*rhs.value);
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

    mpz_set_str(value->mpz, str.c_str(), BASE);
  }

  Integer::Integer(int64_t val) : Integer() {
    mpz_set_si(value->mpz, val);
  }

  size_t Integer::length() const {
    return toString().length();
  }

  Integer Integer::sqrt() const {
    if (*this < 0) {
      throw std::domain_error("Sqrt of a negative number");
    }

    Integer res;
    res.callFunction([this](IntegerImpl &resVal) { mpz_sqrt(resVal.mpz, value->mpz); });
    return res;
  }

  Integer &Integer::operator%=(const Integer &rhs) {
    return mod(rhs);
  }

  Integer Integer::operator%(const Integer &rhs) const {
    return Integer(*this).mod(rhs);
  }

  std::string Integer::toString() const {
    char *tmp = nullptr;
    return mpz_get_str(tmp, BASE, value->mpz);
  }

  bool Integer::equals(const Integer &rhs) const {
    return mpz_cmp(value->mpz, rhs.value->mpz) == 0;
  }

  bool Integer::less(const Integer &rhs) const {
    return mpz_cmp(value->mpz, rhs.value->mpz) == -1;
  }

  bool Integer::more(const Integer &rhs) const {
    return mpz_cmp(value->mpz, rhs.value->mpz) == 1;
  }

  Integer &Integer::add(const Integer &rhs) {
    callFunction([this, &rhs](IntegerImpl &resVal) { mpz_add(resVal.mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::substract(const Integer &rhs) {
    callFunction([this, &rhs](IntegerImpl &resVal) { mpz_sub(resVal.mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::multiply(const Integer &rhs) {
    callFunction([this, &rhs](IntegerImpl &resVal) { mpz_mul(resVal.mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::divide(const Integer &rhs) {
    if (rhs == 0) {
      throw std::domain_error("Division by zero");
    }

    callFunction([this, &rhs](IntegerImpl &resVal) { mpz_tdiv_q(resVal.mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::negate() {
    callFunction([this](IntegerImpl &resVal) { mpz_neg(resVal.mpz, value->mpz); });
    return *this;
  }

  Integer &Integer::increase() {
    callFunction([this](IntegerImpl &resVal) { mpz_add_ui(resVal.mpz, value->mpz, 1); });
    return *this;
  }

  Integer &Integer::decrease() {
    callFunction([this](IntegerImpl &resVal) { mpz_sub_ui(resVal.mpz, value->mpz, 1); });
    return *this;
  }

  Integer &Integer::mod(const Integer &rhs) {
    if (rhs == 0) {
      throw std::domain_error("Modulo by zero");
    }

    callFunction([this, &rhs](IntegerImpl &resVal) { mpz_tdiv_r(resVal.mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::callFunction(const std::function<void(IntegerImpl &)> &func) {
    IntegerImpl res;
    func(res);
    *value = res;
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
