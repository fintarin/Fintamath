#pragma once

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IArithmetic.hpp"
#include "fintamath/exceptions/InvalidInputBinaryOperatorException.hpp"
#include "fintamath/parser/Parser.hpp"

namespace fintamath {

class IIntegral : virtual public IArithmetic {
public:
  friend inline std::unique_ptr<IIntegral> operator%(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.modAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator&(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitAndAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator|(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitOrAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator^(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitXorAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator<<(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitLeftShiftAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator>>(const IIntegral &lhs, const IIntegral &rhs) {
    return lhs.bitRightShiftAbstract(rhs);
  }

  friend inline std::unique_ptr<IIntegral> operator~(const IIntegral &rhs) {
    return rhs.bitNotAbstract();
  }

  template <typename T, typename = std::enable_if_t<std::is_base_of_v<IIntegral, T>>>
  static void registerType() {
    Parser::registerType<T>(parserVector);
  }

  static std::unique_ptr<IIntegral> parse(const std::string &str) {
    return Parser::parse(parserVector, str);
  }

protected:
  virtual std::unique_ptr<IIntegral> modAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitAndAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitOrAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitXorAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitLeftShiftAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitRightShiftAbstract(const IIntegral &rhs) const = 0;

  virtual std::unique_ptr<IIntegral> bitNotAbstract() const = 0;

private:
  static Parser::Vector<std::unique_ptr<IIntegral>, const std::string &> parserVector;
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

  std::unique_ptr<IIntegral> modAbstract(const IIntegral &inRhs) const final {
    return executeAbstract(
        inRhs, "%",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.mod(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs % rhs;
        });
  }

  std::unique_ptr<IIntegral> bitAndAbstract(const IIntegral &inRhs) const override {
    return executeAbstract(
        inRhs, "&",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitAnd(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs & rhs;
        });
  }

  std::unique_ptr<IIntegral> bitOrAbstract(const IIntegral &inRhs) const override {
    return executeAbstract(
        inRhs, "|",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitOr(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs | rhs;
        });
  }

  std::unique_ptr<IIntegral> bitXorAbstract(const IIntegral &inRhs) const override {
    return executeAbstract(
        inRhs, "^",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitXor(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs ^ rhs;
        });
  }

  std::unique_ptr<IIntegral> bitLeftShiftAbstract(const IIntegral &inRhs) const override {
    return executeAbstract(
        inRhs, "<<",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitLeftShift(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs << rhs;
        });
  }

  std::unique_ptr<IIntegral> bitRightShiftAbstract(const IIntegral &inRhs) const override {
    return executeAbstract(
        inRhs, ">>",
        [](IIntegralCRTP<Derived> &lhs, const Derived &rhs) {
          return lhs.bitRightShift(rhs);
        },
        [](const IIntegral &lhs, const IIntegral &rhs) {
          return lhs >> rhs;
        });
  }

  std::unique_ptr<IIntegral> bitNotAbstract() const final {
    return std::make_unique<Derived>(~(*this));
  }

private:
  std::unique_ptr<IIntegral>
  executeAbstract(const IIntegral &rhs, const std::string &oper,
                  std::function<Derived(IIntegralCRTP<Derived> &lhs, const Derived &rhs)> &&f1,
                  std::function<std::unique_ptr<IIntegral>(const IIntegral &, const IIntegral &)> &&f2) const {
    if (const auto *rhpPtr = cast<Derived>(&rhs)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(f1(*lhsPtr, *rhpPtr).toMinimalObject());
    }
    if (std::unique_ptr<IMathObject> rhsPtr = convert(*this, rhs)) {
      auto lhsPtr = cast<IIntegralCRTP<Derived>>(clone());
      return cast<IIntegral>(f1(*lhsPtr, cast<Derived>(*rhsPtr)).toMinimalObject());
    }
    if (std::unique_ptr<IMathObject> lhsPtr = convert(rhs, *this)) {
      return cast<IIntegral>(f2(cast<IIntegral>(*lhsPtr), rhs)->toMinimalObject());
    }
    throw InvalidInputBinaryOperatorException(oper, toString(), rhs.toString());
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
