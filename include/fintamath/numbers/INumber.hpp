#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/core/IComparable.hpp"
#include "fintamath/core/IIncremental.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class INumber : virtual public IComparable {
public:
  virtual bool isPrecise() const {
    return true;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<INumber, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static unique_ptr<INumber> parse(const string &str) {
    return Parser::parse(parserVector, str);
  }

private:
  static Parser::Vector<unique_ptr<INumber>, const string &> parserVector;
};

inline unique_ptr<INumber> operator+(const INumber &lhs, const INumber &rhs) {
  auto res = lhs + cast<IArithmetic>(rhs);
  return cast<INumber>(move(res));
}

inline unique_ptr<INumber> operator-(const INumber &lhs, const INumber &rhs) {
  auto res = lhs - cast<IArithmetic>(rhs);
  return cast<INumber>(move(res));
}

inline unique_ptr<INumber> operator*(const INumber &lhs, const INumber &rhs) {
  auto res = lhs * cast<IArithmetic>(rhs);
  return cast<INumber>(move(res));
}

inline unique_ptr<INumber> operator/(const INumber &lhs, const INumber &rhs) {
  auto res = lhs / cast<IArithmetic>(rhs);
  return cast<INumber>(move(res));
}

template <typename Rhs, typename = std::enable_if_t<std::is_same_v<INumber, Rhs>>>
unique_ptr<INumber> operator+(const Rhs &rhs) {
  return cast<INumber>(+cast<IArithmetic>(rhs));
}

template <typename Rhs, typename = std::enable_if_t<std::is_same_v<INumber, Rhs>>>
unique_ptr<INumber> operator-(const Rhs &rhs) {
  return cast<INumber>(-cast<IArithmetic>(rhs));
}

template <typename Derived>
class INumberCRTP : public IComparableCRTP<Derived>, public INumber {};

}
