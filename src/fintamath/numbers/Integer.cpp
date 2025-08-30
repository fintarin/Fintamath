#include "fintamath/numbers/Integer.hpp"

#include <compare>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <fmt/core.h>

#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/numbers/NumberUtils.hpp"

namespace fintamath {

FINTAMATH_CHILD_CLASS_IMPLEMENTATION(Integer)

using namespace detail;

Integer::Integer(Backend inBackend) : backend(std::move(inBackend)) {
}

Integer::Integer(const std::string_view str) {
  constexpr auto throwInvalidInputException = [](const std::string_view invalidStr) {
    throw InvalidInputException(fmt::format(
        R"(Unable to parse {} from "{}")",
        getClassStatic()->getName(),
        invalidStr));
  };

  if (str.empty()) {
    throwInvalidInputException(str);
  }

  try {
    backend.assign(removeLeadingZeroes(std::string(str)));
  }
  catch (const std::runtime_error &) {
    throwInvalidInputException(str);
  }
}

std::string Integer::toString() const noexcept {
  return backend.str();
}

int Integer::sign() const {
  return backend.sign();
}

const Integer::Backend &Integer::getBackend() const noexcept {
  return backend;
}

bool Integer::equals(const Integer &rhs) const {
  return backend == rhs.backend;
}

std::strong_ordering Integer::compare(const Integer &rhs) const {
  return backend.compare(rhs.backend) <=> 0;
}

Integer &Integer::add(const Integer &rhs) {
  backend += rhs.backend;
  return *this;
}

Integer &Integer::substract(const Integer &rhs) {
  backend -= rhs.backend;
  return *this;
}

Integer &Integer::multiply(const Integer &rhs) {
  backend *= rhs.backend;
  return *this;
}

Integer &Integer::divide(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedException(fmt::format(
        R"(div({}, {}) is undefined (division by zero))",
        toString(),
        rhs.toString()));
  }

  backend /= rhs.backend;
  return *this;
}

Integer &Integer::negate() {
  backend = -backend;
  return *this;
}

Integer &Integer::mod(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedException(fmt::format(
        R"(mod({}, {}) is undefined (modulo by zero))",
        toString(),
        rhs.toString()));
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
        R"(bitLeftShift({}, {}) is undefined (negative shift))",
        toString(),
        rhs.toString()));
  }

  backend <<= static_cast<int64_t>(rhs.backend);
  return *this;
}

Integer &Integer::bitRightShift(const Integer &rhs) {
  if (rhs < 0) {
    throw UndefinedException(fmt::format(
        R"(bitRightShift({}, {}) is undefined (negative shift))",
        toString(),
        rhs.toString()));
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

}
