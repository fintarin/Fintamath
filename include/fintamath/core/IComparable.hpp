#pragma once

#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputBinaryOperatorException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IComparable : virtual public IArithmetic {
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
    Parser::registerType<T>(parserVector, parserFunc);
  }

  static std::unique_ptr<IComparable> parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual bool lessAbstract(const IComparable &rhs) const = 0;

  virtual bool moreAbstract(const IComparable &rhs) const = 0;

private:
  inline static Parser::Vector<std::unique_ptr<IComparable>, const std::string &> parserVector;
};

template <typename Derived>
class IComparableCRTP : virtual public IArithmeticCRTP<Derived>, virtual public IComparable {
public:
  bool operator<(const Derived &rhs) const {
    return less(rhs);
  }

  bool operator>(const Derived &rhs) const {
    return more(rhs);
  }

  bool operator<=(const Derived &rhs) const {
    return !more(rhs);
  }

  bool operator>=(const Derived &rhs) const {
    return !less(rhs);
  }

protected:
  virtual bool less(const Derived &rhs) const = 0;

  virtual bool more(const Derived &rhs) const = 0;

  bool lessAbstract(const IComparable &inRhs) const final {
    return executeAbstract(
        inRhs, "<",
        [](const IComparableCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.less(rhs);
        },
        [](const IComparable &lhs, const IComparable &rhs) {
          return lhs < rhs;
        });
  }

  bool moreAbstract(const IComparable &inRhs) const final {
    return executeAbstract(
        inRhs, ">",
        [](const IComparableCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.more(rhs);
        },
        [](const IComparable &lhs, const IComparable &rhs) {
          return lhs > rhs;
        });
  }

private:
  bool executeAbstract(const IComparable &rhs, const std::string &oper,
                       std::function<bool(const IComparableCRTP<Derived> &lhs, const Derived &rhs)> &&f1,
                       std::function<bool(const IComparable &, const IComparable &)> &&f2) const {
    if (const auto *rhsPtr = cast<Derived>(&rhs)) {
      return f1(*this, *rhsPtr);
    }
    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs); rhsPtr != nullptr) {
      return f1(*this, cast<Derived>(*rhsPtr));
    }
    if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this); lhsPtr != nullptr) {
      return f2(cast<IComparable>(*lhsPtr), rhs);
    }
    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
  }
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
