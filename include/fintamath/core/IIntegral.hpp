#pragma once

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputBinaryOpearatorException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IIntegral;
using IntegralPtr = std::unique_ptr<IIntegral>;

class IIntegral : virtual public IArithmetic {
public:
  friend IntegralPtr operator%(const IIntegral &lhs, const IIntegral &rhs);

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IIntegral, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static IntegralPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual IntegralPtr modAbstract(const IIntegral &rhs) const = 0;

private:
  static Parser::Vector<IntegralPtr, const std::string &> parserVector;
};

inline IntegralPtr operator%(const IIntegral &lhs, const IIntegral &rhs) {
  return lhs.modAbstract(rhs);
}

template <typename Derived>
class IIntegralCRTP : virtual public IArithmeticCRTP<Derived>, virtual public IIntegral {
public:
  Derived &operator%=(const Derived &rhs) {
    return mod(rhs);
  }

  Derived operator%(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) %= rhs;
  }

protected:
  virtual Derived &mod(const Derived &rhs) = 0;

  IntegralPtr modAbstract(const IIntegral &rhs) const final {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(lhsPtr->mod(*rhsPtr).toMinimalObject());
    }
    if (MathObjectPtr rhsPtr = convert(rhs, *this)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(lhsPtr->mod(cast<Derived>(*rhsPtr)).toMinimalObject());
    }
    if (MathObjectPtr lhsPtr = convert(*this, rhs)) {
      return cast<IIntegral>((cast<IIntegral>(*lhsPtr) % rhs)->toMinimalObject());
    }
    throw InvalidInputBinaryOpearatorException("%", toString(), rhs.toString());
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator%=(LhsType &lhs, const RhsType &rhs) {
  return lhs %= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator%(const LhsType &lhs, const RhsType &rhs) {
  return lhs % LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator%(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) % rhs;
}

}
