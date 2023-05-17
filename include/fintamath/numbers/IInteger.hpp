#pragma once

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class IInteger : virtual public INumber {
public:
  friend inline std::unique_ptr<IInteger> operator%(const IInteger &lhs, const IInteger &rhs) {
    return lhs.modAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator&(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitAndAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator|(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitOrAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator^(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitXorAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator<<(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitLeftShiftAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator>>(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitRightShiftAbstract(rhs);
  }

  friend inline std::unique_ptr<IInteger> operator~(const IInteger &rhs) {
    return rhs.bitNotAbstract();
  }

  friend inline IInteger &operator++(IInteger &rhs) {
    return rhs.increaseAbstract();
  }

  friend inline IInteger &operator--(IInteger &rhs) {
    return rhs.decreaseAbstract();
  }

  friend inline std::unique_ptr<IInteger> operator++(IInteger &lhs, int) {
    auto res = cast<IInteger>(lhs.clone());
    lhs.increaseAbstract();
    return res;
  }

  friend inline std::unique_ptr<IInteger> operator--(IInteger &lhs, int) {
    auto res = cast<IInteger>(lhs.clone());
    lhs.decreaseAbstract();
    return res;
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IInteger, T>>>
  static void registerType() {
    Parser::registerType<T>(getParser());
  }

  static std::unique_ptr<IInteger> parse(const std::string &str) {
    return Parser::parse(getParser(), str);
  }

protected:
  virtual std::unique_ptr<IInteger> modAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitAndAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitOrAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitXorAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitLeftShiftAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitRightShiftAbstract(const IInteger &rhs) const = 0;

  virtual std::unique_ptr<IInteger> bitNotAbstract() const = 0;

  virtual IInteger &increaseAbstract() = 0;

  virtual IInteger &decreaseAbstract() = 0;

private:
  static Parser::Vector<std::unique_ptr<IInteger>, const std::string &> &getParser();
};

template <typename Derived>
class IIntegerCRTP : virtual public INumberCRTP<Derived>, virtual public IInteger {
public:
  Derived &operator%=(const Derived &rhs) {
    return mod(rhs);
  }

  Derived operator%(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) %= rhs;
  }

  Derived &operator&=(const Derived &rhs) {
    return bitAnd(rhs);
  }

  Derived operator&(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) &= rhs;
  }

  Derived &operator|=(const Derived &rhs) {
    return bitOr(rhs);
  }

  Derived operator|(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) |= rhs;
  }

  Derived &operator^=(const Derived &rhs) {
    return bitXor(rhs);
  }

  Derived operator^(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) ^= rhs;
  }

  Derived &operator<<=(const Derived &rhs) {
    return bitLeftShift(rhs);
  }

  Derived operator<<(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) <<= rhs;
  }

  Derived &operator>>=(const Derived &rhs) {
    return bitRightShift(rhs);
  }

  Derived operator>>(const Derived &rhs) const {
    return Derived(static_cast<const Derived &>(*this)) >>= rhs;
  }

  Derived operator~() const {
    Derived tmp = Derived(cast<Derived>(*this));
    return static_cast<IIntegerCRTP<Derived> &>(tmp).bitNot();
  }

  Derived &operator++() {
    return increase();
  }

  Derived &operator--() {
    return decrease();
  }

  Derived operator++(int) {
    auto res = Derived(cast<Derived>(*this));
    increase();
    return res;
  }

  Derived operator--(int) {
    auto res = Derived(cast<Derived>(*this));
    decrease();
    return res;
  }

protected:
  virtual Derived &mod(const Derived &rhs) = 0;

  virtual Derived &bitAnd(const Derived &rhs) = 0;

  virtual Derived &bitOr(const Derived &rhs) = 0;

  virtual Derived &bitXor(const Derived &rhs) = 0;

  virtual Derived &bitLeftShift(const Derived &rhs) = 0;

  virtual Derived &bitRightShift(const Derived &rhs) = 0;

  virtual Derived &bitNot() = 0;

  virtual Derived &increase() = 0;

  virtual Derived &decrease() = 0;

  std::unique_ptr<IInteger> modAbstract(const IInteger &inRhs) const final {
    return executeAbstract(
        inRhs, "%",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.mod(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs % rhs;
        });
  }

  std::unique_ptr<IInteger> bitAndAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "&",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitAnd(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs & rhs;
        });
  }

  std::unique_ptr<IInteger> bitOrAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "|",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitOr(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs | rhs;
        });
  }

  std::unique_ptr<IInteger> bitXorAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "^",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitXor(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs ^ rhs;
        });
  }

  std::unique_ptr<IInteger> bitLeftShiftAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, "<<",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitLeftShift(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs << rhs;
        });
  }

  std::unique_ptr<IInteger> bitRightShiftAbstract(const IInteger &inRhs) const override {
    return executeAbstract(
        inRhs, ">>",
        [](IIntegerCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitRightShift(rhs);
        },
        [](const IInteger &lhs, const IInteger &rhs) {
          return lhs >> rhs;
        });
  }

  std::unique_ptr<IInteger> bitNotAbstract() const final {
    return std::make_unique<Derived>(~(*this));
  }

  IInteger &increaseAbstract() final {
    increase();
    return *this;
  }

  IInteger &decreaseAbstract() final {
    decrease();
    return *this;
  }

private:
  template <typename FunctionCommonTypes, typename FunctionDifferentTypes>
  std::unique_ptr<IInteger> executeAbstract(const IInteger &rhs, const std::string &oper,
                                            FunctionCommonTypes &&funcCommonTypes,
                                            FunctionDifferentTypes &&funcDifferentTypes) const {

    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IIntegerCRTP<Derived>>(clone());
      return cast<IInteger>(funcCommonTypes(*lhsPtr, *rhpPtr).toMinimalObject());
    }

    if constexpr (IsConvertible<Derived>::value) {
      if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
        auto lhsPtr = cast<IIntegerCRTP<Derived>>(clone());
        return cast<IInteger>(funcCommonTypes(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
      }

      if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
        return cast<IInteger>(funcDifferentTypes(cast<IInteger>(*lhsPtr), rhs)->toMinimalObject());
      }
    }

    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
  }
};

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator%=(LhsType &lhs, const RhsType &rhs) {
  return lhs %= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator%(const LhsType &lhs, const RhsType &rhs) {
  return lhs % LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator%(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) % rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator&=(LhsType &lhs, const RhsType &rhs) {
  return lhs &= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator&(const LhsType &lhs, const RhsType &rhs) {
  return lhs & LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator&(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) & rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator|=(LhsType &lhs, const RhsType &rhs) {
  return lhs |= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator|(const LhsType &lhs, const RhsType &rhs) {
  return lhs | LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator|(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) | rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator^=(LhsType &lhs, const RhsType &rhs) {
  return lhs ^= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator^(const LhsType &lhs, const RhsType &rhs) {
  return lhs ^ LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator^(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) ^ rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator<<=(LhsType &lhs, const RhsType &rhs) {
  return lhs <<= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator<<(const LhsType &lhs, const RhsType &rhs) {
  return lhs << LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator<<(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) << rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType &operator>>=(LhsType &lhs, const RhsType &rhs) {
  return lhs >>= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, LhsType> && std::is_convertible_v<RhsType, LhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
LhsType operator>>(const LhsType &lhs, const RhsType &rhs) {
  return lhs >> LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IInteger, RhsType> && std::is_convertible_v<LhsType, RhsType> &&
                                      !std::is_same_v<LhsType, RhsType>>>
RhsType operator>>(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) >> rhs;
}

}
