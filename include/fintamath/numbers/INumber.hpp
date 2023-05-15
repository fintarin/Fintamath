#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IIncremental.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class INumber : virtual public IComparable {
  FINTAMATH_CONVERTIBLE()

public:
  virtual bool isPrecise() const {
    return true;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<INumber, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<INumber> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
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
class INumberCRTP : virtual public IComparableCRTP<Derived>, virtual public INumber {};

}
