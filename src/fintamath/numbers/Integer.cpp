#include "fintamath/numbers/Integer.hpp"

#include <compare>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <fmt/format.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/NumberUtils.hpp"

namespace fintamath {

FINTAMATH_CLASS_IMPLEMENTATION(Integer)

Integer::Integer(Backend inBackend) : backend(std::move(inBackend)) {
}

Integer::Integer(const std::string_view str) {
  constexpr auto throwInvalidInputException = [](const std::string_view invalidStr) {
    throw InvalidInputException(fmt::format(
      "Unable to parse {} from \"{}\"",
      getClassStatic()->getName(),
      invalidStr
    ));
  };

  if (str.empty()) {
    throwInvalidInputException(str);
  }

  try {
    backend.assign(detail::removeLeadingZeroes(std::string(str)));
  }
  catch (const std::runtime_error &) {
    throwInvalidInputException(str);
  }
}

std::string Integer::toString() const noexcept {
  return backend.str();
}

bool Integer::isZero() const noexcept {
  return backend.is_zero();
}

int Integer::sign() const {
  return backend.sign();
}

const Integer::Backend &Integer::getBackend() const noexcept {
  return backend;
}

bool Integer::equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept {
  return Super::equals(self, rhs);
}

bool Integer::equals(const Integer &rhs) const noexcept {
  return backend == rhs.backend;
}

std::strong_ordering Integer::compare(const Integer &rhs) const noexcept {
  return backend.compare(rhs.backend) <=> 0;
}

Integer &Integer::add(const Integer &rhs) {
  backend += rhs.backend;
  return *this;
}

Integer &Integer::sub(const Integer &rhs) {
  backend -= rhs.backend;
  return *this;
}

Integer &Integer::mul(const Integer &rhs) {
  backend *= rhs.backend;
  return *this;
}

Integer &Integer::div(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedException(fmt::format(
      "div({}, {}) is undefined (division by zero)",
      toString(),
      rhs.toString()
    ));
  }

  backend /= rhs.backend;
  return *this;
}

Integer &Integer::neg() {
  backend = -backend;
  return *this;
}

Integer &Integer::mod(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedException(fmt::format(
      "mod({}, {}) is undefined (modulo by zero)",
      toString(),
      rhs.toString()
    ));
  }

  backend %= rhs.backend;
  return *this;
}

Integer &Integer::bitAnd(const Integer &rhs) {
  backend &= rhs.backend;
  return *this;
}

Integer &Integer::bitOr(const Integer &rhs) {
  backend |= rhs.backend;
  return *this;
}

Integer &Integer::bitXor(const Integer &rhs) {
  backend ^= rhs.backend;
  return *this;
}

Integer &Integer::bitLeftShift(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedException(fmt::format(
      "bitLeftShift({}, {}) is undefined (negative shift)",
      toString(),
      rhs.toString()
    ));
  }

  backend <<= static_cast<int64_t>(rhs.backend);
  return *this;
}

Integer &Integer::bitRightShift(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedException(fmt::format(
      "bitRightShift({}, {}) is undefined (negative shift)",
      toString(),
      rhs.toString()
    ));
  }

  backend >>= static_cast<int64_t>(rhs.backend);
  return *this;
}

Integer &Integer::bitNot() {
  backend = ~backend;
  return *this;
}

Integer &Integer::increase() {
  ++backend;
  return *this;
}

Integer &Integer::decrease() {
  --backend;
  return *this;
}

Integer &Integer::operator%=(const Integer &rhs) {
  return mod(rhs);
}

Integer &Integer::operator&=(const Integer &rhs) {
  return bitAnd(rhs);
}

Integer &Integer::operator|=(const Integer &rhs) {
  return bitOr(rhs);
}

Integer &Integer::operator^=(const Integer &rhs) {
  return bitXor(rhs);
}

Integer &Integer::operator<<=(const Integer &rhs) {
  return bitLeftShift(rhs);
}

Integer &Integer::operator>>=(const Integer &rhs) {
  return bitRightShift(rhs);
}

Integer Integer::operator%(const Integer &rhs) const {
  return Integer(*this) %= rhs;
}

Integer Integer::operator&(const Integer &rhs) const {
  return Integer(*this) &= rhs;
}

Integer Integer::operator|(const Integer &rhs) const {
  return Integer(*this) |= rhs;
}

Integer Integer::operator^(const Integer &rhs) const {
  return Integer(*this) ^= rhs;
}

Integer Integer::operator<<(const Integer &rhs) const {
  return Integer(*this) <<= rhs;
}

Integer Integer::operator>>(const Integer &rhs) const {
  return Integer(*this) >>= rhs;
}

Integer Integer::operator~() const {
  Integer tmp = Integer(*this);
  return tmp.bitNot();
}

Integer &Integer::operator++() {
  return increase();
}

Integer &Integer::operator--() {
  return decrease();
}

Integer Integer::operator++(int) {
  Integer res = *this;
  increase();
  return res;
}

Integer Integer::operator--(int) {
  Integer res = *this;
  decrease();
  return res;
}

const SharedRef<Integer>& Integer::getZero() {
  static const SharedRef<Integer> zero = makeShared<Integer>(0);
  return zero;
}

const SharedRef<Integer>& Integer::getOne() {
  static const SharedRef<Integer> one = makeShared<Integer>(1);
  return one;
}

const SharedRef<Integer>& Integer::getNegOne() {
  static const SharedRef<Integer> neg = makeShared<Integer>(-1);
  return neg;
}

void Integer::registerDefaultObject() const {
  registerEqualsFunction<Integer>();
  registerLessFunction<Integer>();
  registerGreaterFunction<Integer>();
  registerLessEqualsFunction<Integer>();
  registerGreaterEqualsFunction<Integer>();
  registerAddFunction<Integer>();
  registerSubFunction<Integer>();
  registerMulFunction<Integer>();
  registerNegFunction<Integer>();

  // registerDivFunction is called in Rational 
}

}
