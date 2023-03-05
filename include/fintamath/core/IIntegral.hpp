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
  friend inline IntegralPtr operator%(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.modAbstract(rhs);
  }

  friend inline IntegralPtr operator&(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitAndAbstract(rhs);
  }

  friend inline IntegralPtr operator|(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitOrAbstract(rhs);
  }

  friend inline IntegralPtr operator^(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitXorAbstract(rhs);
  }

  friend inline IntegralPtr operator<<(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitLeftShiftAbstract(rhs);
  }

  friend inline IntegralPtr operator>>(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitRightShiftAbstract(rhs);
  }

  friend inline IntegralPtr operator~(const IIntegral &rhs) {
    return rhs.bitNotAbstract();
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IIntegral, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static IntegralPtr parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual IntegralPtr modAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitAndAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitOrAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitXorAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitLeftShiftAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitRightShiftAbstract(const IIntegral &rhs) const = 0;

  virtual IntegralPtr bitNotAbstract() const = 0;

private:
  static Parser::Vector<IntegralPtr, const std::string &> parserVector;
};

template <typename Derived>
class IIntegralCRTP : virtual public IArithmeticCRTP<Derived>, virtual public IIntegral {
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
    return static_cast<IIntegralCRTP<Derived> &>(tmp).bitNot();
  }

protected:
  virtual Derived &mod(const Derived &rhs) = 0;

  virtual Derived &bitAnd(const Derived &rhs) = 0;

  virtual Derived &bitOr(const Derived &rhs) = 0;

  virtual Derived &bitXor(const Derived &rhs) = 0;

  virtual Derived &bitLeftShift(const Derived &rhs) = 0;

  virtual Derived &bitRightShift(const Derived &rhs) = 0;

  virtual Derived &bitNot() = 0;

  IntegralPtr modAbstract(const IIntegral &rhs) const final {
    return executeAbstract(
        rhs, "%",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.mod(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs % rhs;
        });
  }

  IntegralPtr bitAndAbstract(const IIntegral &rhs) const override {
    return executeAbstract(
        rhs, "&",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitAnd(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs & rhs;
        });
  }

  IntegralPtr bitOrAbstract(const IIntegral &rhs) const override {
    return executeAbstract(
        rhs, "|",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitOr(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs | rhs;
        });
  }

  IntegralPtr bitXorAbstract(const IIntegral &rhs) const override {
    return executeAbstract(
        rhs, "^",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitXor(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs ^ rhs;
        });
  }

  IntegralPtr bitLeftShiftAbstract(const IIntegral &rhs) const override {
    return executeAbstract(
        rhs, "<<",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitLeftShift(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs << rhs;
        });
  }

  IntegralPtr bitRightShiftAbstract(const IIntegral &rhs) const override {
    return executeAbstract(
        rhs, ">>",
        [this](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitRightShift(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs >> rhs;
        });
  }

  IntegralPtr bitNotAbstract() const final {
    return std::make_unique<Derived>(~(*this));
  }

private:
  IntegralPtr executeAbstract(const IIntegral &rhs, const std::string &oper,
                              std::function<Derived(IIntegralCRTP<Derived> &lhs, const Derived &rhs)> &&f1,
                              std::function<IntegralPtr(const IIntegral &, const IIntegral &)> &&f2) const {
    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(f1(*lhsPtr, *rhpPtr).toMinimalObject());
    }
    if (MathObjectPtr rhsPtr = convert(rhs, *this)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(f1(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
    }
    if (MathObjectPtr lhsPtr = convert(*this, rhs)) {
      return cast<IIntegral>(f2(cast<IIntegral>(*lhsPtr), rhs)->toMinimalObject());
    }
    throw InvalidInputBinaryOpearatorException(oper, toString(), rhs.toString());
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

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator&=(LhsType &lhs, const RhsType &rhs) {
  return lhs &= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator&(const LhsType &lhs, const RhsType &rhs) {
  return lhs & LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator&(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) & rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator|=(LhsType &lhs, const RhsType &rhs) {
  return lhs |= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator|(const LhsType &lhs, const RhsType &rhs) {
  return lhs | LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator|(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) | rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator^=(LhsType &lhs, const RhsType &rhs) {
  return lhs ^= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator^(const LhsType &lhs, const RhsType &rhs) {
  return lhs ^ LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator^(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) ^ rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator<<=(LhsType &lhs, const RhsType &rhs) {
  return lhs <<= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator<<(const LhsType &lhs, const RhsType &rhs) {
  return lhs << LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator<<(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) << rhs;
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType &operator>>=(LhsType &lhs, const RhsType &rhs) {
  return lhs >>= LhsType(rhs);
}

template <typename LhsType, typename RhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, LhsType> &&
                                      std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
LhsType operator>>(const LhsType &lhs, const RhsType &rhs) {
  return lhs >> LhsType(rhs);
}

template <typename RhsType, typename LhsType,
          typename = std::enable_if_t<std::is_base_of_v<IIntegral, RhsType> &&
                                      std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
RhsType operator>>(const LhsType &lhs, const RhsType &rhs) {
  return RhsType(lhs) >> rhs;
}

}
