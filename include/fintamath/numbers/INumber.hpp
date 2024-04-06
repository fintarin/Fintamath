#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/MathObjectClass.hpp"
#include "fintamath/core/MathObjectUtils.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class INumber : public IComparable {
  FINTAMATH_PARENT_CLASS_BODY(INumber, IComparable)

public:
  virtual bool isPrecise() const {
    return true;
  }

  virtual bool isComplex() const {
    return false;
  }
};

inline std::unique_ptr<INumber> operator+(const INumber &lhs, const INumber &rhs) {
  auto res = lhs + cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline std::unique_ptr<INumber> operator-(const INumber &lhs, const INumber &rhs) {
  auto res = lhs - cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline std::unique_ptr<INumber> operator*(const INumber &lhs, const INumber &rhs) {
  auto res = lhs * cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

inline std::unique_ptr<INumber> operator/(const INumber &lhs, const INumber &rhs) {
  auto res = lhs / cast<IArithmetic>(rhs);
  return cast<INumber>(std::move(res));
}

template <std::same_as<INumber> Rhs>
std::unique_ptr<INumber> operator+(const Rhs &rhs) {
  return cast<INumber>(+cast<IArithmetic>(rhs));
}

template <std::same_as<INumber> Rhs>
std::unique_ptr<INumber> operator-(const Rhs &rhs) {
  return cast<INumber>(-cast<IArithmetic>(rhs));
}

template <typename Derived>
class INumberCRTP : public INumber {
#define I_NUMBER_CRTP INumberCRTP<Derived>
#include "fintamath/numbers/INumberCRTP.hpp"
#undef I_NUMBER_CRTP
};

}
