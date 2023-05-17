#pragma once

#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class IInteger : public INumber {
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
class IIntegerCRTP : public IInteger {
#define FINTAMATH_I_INTEGER_CRTP IIntegerCRTP<Derived>
#include "fintamath/numbers/IIntegerCRTP.hpp"
#undef FINTAMATH_I_INTEGER_CRTP
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
