#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class INumber : public IComparable {
  FINTAMATH_CONVERTIBLE()

public:
  virtual bool isPrecise() const {
    return true;
  }

  virtual bool isComplex() const {
    return false;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<INumber, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<INumber, T>>>
  static void registerType(Parser::Function<std::unique_ptr<INumber>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<INumber> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::INumber;
  }

private:
  static Parser::Vector<std::unique_ptr<INumber>, const std::string &> &getParser();
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

template <typename Rhs, typename = std::enable_if_t<std::is_same_v<INumber, Rhs>>>
std::unique_ptr<INumber> operator+(const Rhs &rhs) {
  return cast<INumber>(+cast<IArithmetic>(rhs));
}

template <typename Rhs, typename = std::enable_if_t<std::is_same_v<INumber, Rhs>>>
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
