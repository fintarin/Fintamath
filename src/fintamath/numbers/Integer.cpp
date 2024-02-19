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

using namespace detail;

Integer::Integer(Backend inBackend) : backend(std::move(inBackend)) {
}

Integer::Integer(const std::string_view str) {
  if (str.empty()) {
    throw InvalidInputException(fmt::format(R"(Invalid {} "")", getTypeStatic().getName()));
  }

  try {
    backend.assign(removeLeadingZeroes(std::string(str)));
  }
  catch (const std::runtime_error &) {
    throw InvalidInputException(fmt::format(R"(Invalid {} "{}")", getTypeStatic().getName(), str));
  }
}

Integer::Integer(const int64_t val) : backend(val) {
}

std::string Integer::toString() const {
  return backend.str();
}

int Integer::sign() const {
  return backend.sign();
}

const Integer::Backend &Integer::getBackend() const {
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
    throw UndefinedException(fmt::format(R"(Undefined "{}" / "{}" (division by zero))", toString(), rhs.toString()));
  }

  backend /= rhs.backend;
  return *this;
}

Integer &Integer::mod(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedException(fmt::format(R"(Undefined "{}" % "{}" (modulo by zero))", toString(), rhs.toString()));
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
  try {
    backend <<= static_cast<int64_t>(rhs.backend);
    return *this;
  }
  catch (...) {
    throw UndefinedException(fmt::format(R"(Undefined "{}" / "{}" (negative shift))", toString(), rhs.toString()));
  }
}

Integer &Integer::bitRightShift(const Integer &rhs) {
  try {
    backend >>= static_cast<int64_t>(rhs.backend);
    return *this;
  }
  catch (...) {
    throw UndefinedException(fmt::format(R"(Undefined "{}" >> "{}" (negative shift))", toString(), rhs.toString()));
  }
}

Integer &Integer::bitNot() {
  backend = ~backend;
  return *this;
}

Integer &Integer::negate() {
  backend = -backend;
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

}
