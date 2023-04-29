#include "fintamath/numbers/Integer.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

#include "fintamath/exceptions/UndefinedBinaryOperatorException.hpp"
#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/numbers/NumberImpls.hpp"

namespace fintamath {

Integer::Integer() {
  impl = std::make_unique<IntegerImpl>();
}

Integer::Integer(const Integer &rhs) : Integer() {
  impl->v.assign(rhs.impl->v);
}

Integer::Integer(Integer &&rhs) noexcept : Integer() {
  impl = std::move(rhs.impl);
}

Integer &Integer::operator=(const Integer &rhs) {
  if (this != &rhs) {
    impl = std::make_unique<IntegerImpl>(*rhs.impl);
  }
  return *this;
}

Integer &Integer::operator=(Integer &&rhs) noexcept {
  if (this != &rhs) {
    impl = std::move(rhs.impl);
  }
  return *this;
}

Integer::~Integer() = default;

Integer::Integer(const IntegerImpl &inImpl) : impl(std::make_unique<IntegerImpl>(inImpl)) {
}

Integer::Integer(std::string str) : Integer() {
  if (str.empty()) {
    throw InvalidInputException(str);
  }

  // Remove leading zeros
  {
    size_t i = 0;
    if (str.front() == '-') {
      i++;
    }

    str.erase(i, str.find_first_not_of('0'));
    if (str.empty()) {
      str = "0";
    }
  }

  try {
    impl->v.assign(str);
  }
  catch (const std::runtime_error &) {
    throw InvalidInputException(str);
  }
}

Integer::Integer(int64_t val) : Integer() {
  impl->v.assign(val);
}

std::string Integer::toString() const {
  return impl->v.str();
}

int Integer::sign() const {
  return impl->v.sign();
}

Integer::operator long long() const {
  return impl->v.convert_to<long long>();
}

const std::unique_ptr<IntegerImpl> &Integer::getImpl() const {
  return impl;
}

bool Integer::equals(const Integer &rhs) const {
  return impl->v == rhs.impl->v;
}

bool Integer::less(const Integer &rhs) const {
  return impl->v < rhs.impl->v;
}

bool Integer::more(const Integer &rhs) const {
  return impl->v > rhs.impl->v;
}

Integer &Integer::add(const Integer &rhs) {
  impl->v += rhs.impl->v;
  return *this;
}

Integer &Integer::substract(const Integer &rhs) {
  impl->v -= rhs.impl->v;
  return *this;
}

Integer &Integer::multiply(const Integer &rhs) {
  impl->v *= rhs.impl->v;
  return *this;
}

Integer &Integer::divide(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedBinaryOperatorException("/", toString(), rhs.toString());
  }

  impl->v /= rhs.impl->v;
  return *this;
}

Integer &Integer::mod(const Integer &rhs) {
  if (rhs == 0) {
    throw UndefinedBinaryOperatorException("mod", toString(), rhs.toString());
  }

  impl->v %= rhs.impl->v;
  return *this;
}

Integer &Integer::bitAnd(const Integer &rhs) {
  impl->v &= rhs.impl->v;
  return *this;
}

Integer &Integer::bitOr(const Integer &rhs) {
  impl->v |= rhs.impl->v;
  return *this;
}

Integer &Integer::bitXor(const Integer &rhs) {
  impl->v ^= rhs.impl->v;
  return *this;
}

Integer &Integer::bitLeftShift(const Integer &rhs) {
  try {
    impl->v <<= int64_t(rhs.impl->v);
    return *this;
  }
  catch (...) {
    throw UndefinedBinaryOperatorException("<<", toString(), rhs.toString());
  }
}

Integer &Integer::bitRightShift(const Integer &rhs) {
  try {
    impl->v >>= int64_t(rhs.impl->v);
    return *this;
  }
  catch (...) {
    throw UndefinedBinaryOperatorException(">>", toString(), rhs.toString());
  }
}

Integer &Integer::bitNot() {
  impl->v = ~impl->v;
  return *this;
}

Integer &Integer::negate() {
  impl->v = -impl->v;
  return *this;
}

Integer &Integer::increase() {
  ++impl->v;
  return *this;
}

Integer &Integer::decrease() {
  --impl->v;
  return *this;
}
}
