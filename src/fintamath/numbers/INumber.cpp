#include "fintamath/numbers/INumber.hpp"

#include <fmt/core.h>

#include "fintamath/core/Converter.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

FINTAMATH_INTERFACE_IMPLEMENTATION(INumber)

namespace {

auto callBinaryMultimethod(const auto &multimethod, const Shared<INumber> &lhs, const Shared<INumber> &rhs) {
  assert(lhs && rhs);

  auto res = multimethod(lhs, rhs);

  if (!res) {
    if (auto convRhs = convert(lhs, rhs)) {
      res = multimethod(lhs, convRhs);
    }
    else if (auto convLhs = convert(rhs, lhs)) {
      res = multimethod(convLhs, rhs);
    }
  }

  return res;
}

}

std::optional<unsigned> INumber::getPrecision() const noexcept {
  return {};
}

bool INumber::isComplex() const noexcept {
  return false;
}

bool INumber::equals(const Shared<IMathObject> &lhs, const Shared<IMathObject> &rhs) const noexcept {
  const auto rhsNum = cast<INumber>(rhs);
  if (!rhsNum) {
    return false;
  }

  const auto lhsNum = cast<INumber>(lhs);

  auto res = callBinaryMultimethod(INumber::getEqualsMultimethod(), lhsNum, rhsNum);
  return res.value_or(false);
}

Shared<INumber> add(const Shared<INumber> &lhs, const Shared<INumber> &rhs) {
  auto res = callBinaryMultimethod(INumber::getAddMultimethod(), lhs, rhs);

  if (!res) {
    throw InvalidInputException(fmt::format(
      R"(Unable to call add with arguments {} and {})",
      lhs->getClass()->getName(),
      rhs->getClass()->getName()
    ));
  }

  return *res;
}

INumber::BoolBinaryMultiMethod &INumber::getEqualsMultimethod() {
  static BoolBinaryMultiMethod multimethod;
  return multimethod;
}

INumber::NumberBinaryMultiMethod &INumber::getAddMultimethod() {
  static NumberBinaryMultiMethod multimethod;
  return multimethod;
}

}
