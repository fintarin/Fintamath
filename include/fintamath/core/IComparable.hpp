#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IComparable : public IArithmetic {
public:
  friend inline bool operator<(const IComparable &lhs, const IComparable &rhs) {
    return lhs.lessAbstract(rhs);
  }

  friend inline bool operator>(const IComparable &lhs, const IComparable &rhs) {
    return lhs.moreAbstract(rhs);
  }

  friend inline bool operator<=(const IComparable &lhs, const IComparable &rhs) {
    return !lhs.moreAbstract(rhs);
  }

  friend inline bool operator>=(const IComparable &lhs, const IComparable &rhs) {
    return !lhs.lessAbstract(rhs);
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IComparable, T>>>
  static void registerType(Parser::Function<std::unique_ptr<IComparable>, const std::string &> &&parserFunc) {
    Parser::registerType<T>(getParser(), std::move(parserFunc));
  }

  static std::unique_ptr<IComparable> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IComparable);
  }

protected:
  virtual bool lessAbstract(const IComparable &rhs) const = 0;

  virtual bool moreAbstract(const IComparable &rhs) const = 0;

private:
  static Parser::Vector<std::unique_ptr<IComparable>, const std::string &> &getParser();
};

template <typename Derived>
class IComparableCRTP : public IComparable {
#define FINTAMATH_I_COMPARABLE_CRTP IComparableCRTP<Derived>
#include "fintamath/core/IComparableCRTP.hpp"
#undef FINTAMATH_I_COMPARABLE_CRTP
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<(const LhsType &lhs, const RhsType &rhs) {
  return lhs < LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) < rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>(const LhsType &lhs, const RhsType &rhs) {
  return lhs > LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) > rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<=(const LhsType &lhs, const RhsType &rhs) {
  return lhs <= LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator<=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) <= rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>=(const LhsType &lhs, const RhsType &rhs) {
  return lhs >= LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IComparable, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
bool operator>=(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) >= rhs;
}

}
