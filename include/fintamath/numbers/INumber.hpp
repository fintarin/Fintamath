#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class INumber : public IComparable {
  using NumberParser = detail::Parser<std::unique_ptr<INumber>()>;

public:
  virtual bool isPrecise() const {
    return true;
  }

  virtual bool isComplex() const {
    return false;
  }

  static std::unique_ptr<INumber> parse(const std::string &str) {
    return getParser().parse(str);
  }

  template <std::derived_from<INumber> T>
  static void registerType() {
    getParser().registerType<T>();
  }

  static void registerType(NumberParser::StringConstructor constructor) {
    getParser().registerType(std::move(constructor));
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::INumber, "INumber"};
  }

private:
  static NumberParser &getParser();
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
