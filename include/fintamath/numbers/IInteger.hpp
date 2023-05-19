#pragma once

#include "fintamath/numbers/INumber.hpp"

#define REQUIRE_INTEGERS(Lhs, Rhs)                                                                                     \
  template <typename Lhs, typename Rhs,                                                                                \
            typename = std::enable_if_t<std::is_base_of_v<IInteger, Lhs> && std::is_convertible_v<Rhs, Lhs> &&         \
                                        !std::is_same_v<Lhs, Rhs>>>

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

  static MathObjectTypeId getTypeIdStatic() {
    return MathObjectTypeId(MathObjectType::IInteger);
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

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator%=(Lhs &lhs, const Rhs &rhs) {
  return lhs %= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator%(const Lhs &lhs, const Rhs &rhs) {
  return lhs % Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator%(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) % rhs;
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator&=(Lhs &lhs, const Rhs &rhs) {
  return lhs &= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator&(const Lhs &lhs, const Rhs &rhs) {
  return lhs & Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator&(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) & rhs;
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator|=(Lhs &lhs, const Rhs &rhs) {
  return lhs |= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator|(const Lhs &lhs, const Rhs &rhs) {
  return lhs | Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator|(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) | rhs;
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator^=(Lhs &lhs, const Rhs &rhs) {
  return lhs ^= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator^(const Lhs &lhs, const Rhs &rhs) {
  return lhs ^ Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator^(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) ^ rhs;
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator<<=(Lhs &lhs, const Rhs &rhs) {
  return lhs <<= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator<<(const Lhs &lhs, const Rhs &rhs) {
  return lhs << Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator<<(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) << rhs;
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs &operator>>=(Lhs &lhs, const Rhs &rhs) {
  return lhs >>= Lhs(rhs);
}

REQUIRE_INTEGERS(Lhs, Rhs) Lhs operator>>(const Lhs &lhs, const Rhs &rhs) {
  return lhs >> Lhs(rhs);
}

REQUIRE_INTEGERS(Rhs, Lhs) Rhs operator>>(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) >> rhs;
}

}

#undef REQUIRE_INTEGERS
