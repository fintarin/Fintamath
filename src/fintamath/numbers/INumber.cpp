#include "fintamath/numbers/INumber.hpp"

#include <fmt/core.h>

#include "fintamath/core/Converter.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(INumber)

namespace {

auto callMultimethod(const auto &multimethod, const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  auto res = multimethod(lhs, rhs);

  if (!res) {
    if (auto convRhs = convert(lhs, rhs)) {
      res = multimethod(lhs, convRhs.toRef());
    }
    else if (auto convLhs = convert(rhs, lhs)) {
      res = multimethod(convLhs.toRef(), rhs);
    }
  }

  return res;
}

auto callMultimethod(const auto &multimethod, const SharedRef<INumber> &rhs) {
  return multimethod(rhs);
}

void throwInvalidInputException(const std::string_view funcName, const MathObjectClass lhsClass, const MathObjectClass rhsClass) {
  throw InvalidInputException(fmt::format(
    "Unable to call {} with arguments {} and {}",
    funcName,
    lhsClass->getName(),
    rhsClass->getName()
  ));
}

void throwInvalidInputException(const std::string_view funcName, const MathObjectClass rhsClass) {
  throw InvalidInputException(fmt::format(
    "Unable to call {} with argument",
    funcName,
    rhsClass->getName()
  ));
}

}

std::optional<unsigned> INumber::getPrecision() const noexcept {
  return std::nullopt;
}

bool INumber::isComplex() const noexcept {
  return false;
}

bool INumber::equals(const SharedRef<IMathObject> &self, const SharedRef<IMathObject> &rhs) const noexcept {
  const auto rhsNum = cast<INumber>(rhs);
  if (!rhsNum) {
    return false;
  }

  const auto selfNum = cast<INumber>(self);

  if (static_cast<bool>(selfNum->getPrecision()) != static_cast<bool>(rhsNum->getPrecision())) {
    return false;
  }

  std::optional<bool> res = callMultimethod(INumber::getEqualsMultimethod(), selfNum.toRef(), rhsNum.toRef());
  return res.value_or(false);
}

bool less(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<bool> res = callMultimethod(INumber::getLessMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("less", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

bool greater(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<bool> res = callMultimethod(INumber::getGreaterMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("greater", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

bool lessEquals(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<bool> res = callMultimethod(INumber::getLessEqualsMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("lessEquals", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

bool greaterEquals(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<bool> res = callMultimethod(INumber::getGreaterEqualsMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("greaterEquals", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

SharedRef<INumber> add(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<SharedRef<INumber>> res = callMultimethod(INumber::getAddMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("add", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

SharedRef<INumber> sub(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  std::optional<SharedRef<INumber>> res = callMultimethod(INumber::getSubMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("sub", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

SharedRef<INumber> mul(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  if (lhs->isZero() && !lhs->getPrecision()) {
    return lhs;
  }
  if (rhs->isZero() && !rhs->getPrecision()) {
    return rhs;
  }

  std::optional<SharedRef<INumber>> res = callMultimethod(INumber::getMulMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("mul", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

SharedRef<INumber> div(const SharedRef<INumber> &lhs, const SharedRef<INumber> &rhs) {
  if (lhs->isZero() && !lhs->getPrecision() && !rhs->isZero()) {
    return lhs;
  }

  std::optional<SharedRef<INumber>> res = callMultimethod(INumber::getDivMultimethod(), lhs, rhs);

  if (!res) {
    throwInvalidInputException("div", lhs->getClass(), rhs->getClass());
  }

  return *res;
}

SharedRef<INumber> neg(const SharedRef<INumber> &rhs) {
  std::optional<SharedRef<INumber>> res = callMultimethod(INumber::getNegMultimethod(), rhs);

  if (!res) {
    throwInvalidInputException("neg", rhs->getClass());
  }

  return *res;
}

INumber::BoolBinaryMultiMethod &INumber::getEqualsMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::BoolBinaryMultiMethod &INumber::getLessMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::BoolBinaryMultiMethod &INumber::getGreaterMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::BoolBinaryMultiMethod &INumber::getLessEqualsMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::BoolBinaryMultiMethod &INumber::getGreaterEqualsMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberBinaryMultiMethod &INumber::getAddMultimethod() {
  static NumberBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberBinaryMultiMethod &INumber::getSubMultimethod() {
  static NumberBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberBinaryMultiMethod &INumber::getMulMultimethod() {
  static NumberBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberBinaryMultiMethod &INumber::getDivMultimethod() {
  static NumberBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberUnaryMultiMethod &INumber::getNegMultimethod() {
  static NumberUnaryMultiMethod multimethod;
  return multimethod;
}

}
