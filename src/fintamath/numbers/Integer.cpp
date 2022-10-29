#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "gmp/mini-gmp.h"

#include "fintamath/exceptions/UndefinedBinaryOpearatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(disable : 4244)
#endif

namespace fintamath {
  constexpr int64_t BASE = 10;

  struct IntegerImpl {
    mpz_t mpz{};

    IntegerImpl() {
      mpz_init_set_si(mpz, 0);
    }

    ~IntegerImpl() {
      mpz_clear(mpz);
    }
  };

  Integer::Integer() {
    value = std::make_unique<IntegerImpl>();
  }

  Integer::Integer(const Integer &rhs) : Integer() {
    mpz_set(value->mpz, rhs.value->mpz);
  }

  Integer::Integer(Integer &&rhs) noexcept : value(std::move(rhs.value)) {
  }

  Integer &Integer::operator=(const Integer &rhs) {
    if (this != &rhs) {
      value = std::make_unique<IntegerImpl>();
      mpz_set(value->mpz, rhs.value->mpz);
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
    if (mpz_set_str(value->mpz, str.c_str(), BASE) != 0) {
      throw InvalidInputException("Integer", str);
    }
  }

  Integer::Integer(int64_t val) : Integer() {
    mpz_init_set_si(value->mpz, val);
  }

  size_t Integer::length() const {
    return toString().length();
  }

  Integer Integer::sqrt() const {
    if (*this < 0) {
      throw UndefinedFunctionException("sqrt", {toString()});
    }

    Integer res;
    res.callFunction([this](Integer &tmpRes) { mpz_sqrt(tmpRes.value->mpz, value->mpz); });
    return res;
  }

  Integer &Integer::operator%=(const Integer &rhs) {
    return mod(rhs);
  }

  Integer Integer::operator%(const Integer &rhs) const {
    return Integer(*this).mod(rhs);
  }

  std::string Integer::toString() const {
    char *tmp = mpz_get_str(nullptr, BASE, value->mpz);
    std::string res = tmp;
    free(tmp);
    return res;
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
    callFunction([this, &rhs](Integer &res) { mpz_add(res.value->mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::substract(const Integer &rhs) {
    callFunction([this, &rhs](Integer &res) { mpz_sub(res.value->mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::multiply(const Integer &rhs) {
    callFunction([this, &rhs](Integer &res) { mpz_mul(res.value->mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::divide(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("/", toString(), rhs.toString());
    }

    callFunction([this, &rhs](Integer &res) { mpz_tdiv_q(res.value->mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::negate() {
    callFunction([this](Integer &res) { mpz_neg(res.value->mpz, value->mpz); });
    return *this;
  }

  Integer &Integer::increase() {
    callFunction([this](Integer &res) { mpz_add_ui(res.value->mpz, value->mpz, 1); });
    return *this;
  }

  Integer &Integer::decrease() {
    callFunction([this](Integer &res) { mpz_sub_ui(res.value->mpz, value->mpz, 1); });
    return *this;
  }

  Integer &Integer::mod(const Integer &rhs) {
    if (rhs == 0) {
      throw UndefinedBinaryOpearatorException("mod", toString(), rhs.toString());
    }

    callFunction([this, &rhs](Integer &res) { mpz_tdiv_r(res.value->mpz, value->mpz, rhs.value->mpz); });
    return *this;
  }

  Integer &Integer::callFunction(const std::function<void(Integer &)> &func) {
    Integer res;
    func(res);
    return *this = std::move(res);
  }
}
