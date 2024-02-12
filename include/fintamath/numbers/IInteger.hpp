#pragma once

#include <concepts>
#include <memory>
#include <string>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/MathObjectTypes.hpp"
#include "fintamath/core/Parser.hpp"
#include "fintamath/numbers/INumber.hpp"

namespace fintamath {

class IInteger : public INumber {
  using IntegerParser = Parser<std::unique_ptr<IInteger>()>;

public:
  friend std::unique_ptr<IInteger> operator%(const IInteger &lhs, const IInteger &rhs) {
    return lhs.modAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator&(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitAndAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator|(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitOrAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator^(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitXorAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator<<(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitLeftShiftAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator>>(const IInteger &lhs, const IInteger &rhs) {
    return lhs.bitRightShiftAbstract(rhs);
  }

  friend std::unique_ptr<IInteger> operator~(const IInteger &rhs) {
    return rhs.bitNotAbstract();
  }

  friend IInteger &operator++(IInteger &rhs) {
    return rhs.increaseAbstract();
  }

  friend IInteger &operator--(IInteger &rhs) {
    return rhs.decreaseAbstract();
  }

  friend std::unique_ptr<IInteger> operator++(IInteger &lhs, int) {
    auto res = cast<IInteger>(lhs.clone());
    lhs.increaseAbstract();
    return res;
  }

  friend std::unique_ptr<IInteger> operator--(IInteger &lhs, int) {
    auto res = cast<IInteger>(lhs.clone());
    lhs.decreaseAbstract();
    return res;
  }

  static std::unique_ptr<IInteger> parse(const std::string &str) {
    return getParser().parse(str);
  }

  template <std::derived_from<IInteger> T>
  static void registerType() {
    getParser().registerType<T>();
  }

  static constexpr MathObjectType getTypeStatic() {
    return MathObjectType::IInteger;
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
  static IntegerParser &getParser();
};

template <typename Derived>
class IIntegerCRTP : public IInteger {
#define I_INTEGER_CRTP IIntegerCRTP<Derived>
#include "fintamath/numbers/IIntegerCRTP.hpp"
#undef I_INTEGER_CRTP
};

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator%=(Lhs &lhs, const Rhs &rhs) {
  return lhs %= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator&=(Lhs &lhs, const Rhs &rhs) {
  return lhs &= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator|=(Lhs &lhs, const Rhs &rhs) {
  return lhs |= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator^=(Lhs &lhs, const Rhs &rhs) {
  return lhs ^= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator<<=(Lhs &lhs, const Rhs &rhs) {
  return lhs <<= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator>>=(Lhs &lhs, const Rhs &rhs) {
  return lhs >>= Lhs(rhs);
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator%(const Lhs &lhs, const Rhs &rhs) {
  return lhs % Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator%(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) % rhs;
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator&(const Lhs &lhs, const Rhs &rhs) {
  return lhs & Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator&(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) & rhs;
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator|(const Lhs &lhs, const Rhs &rhs) {
  return lhs | Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator|(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) | rhs;
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator^(const Lhs &lhs, const Rhs &rhs) {
  return lhs ^ Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator^(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) ^ rhs;
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator<<(const Lhs &lhs, const Rhs &rhs) {
  return lhs << Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator<<(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) << rhs;
}

template <std::derived_from<IInteger> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator>>(const Lhs &lhs, const Rhs &rhs) {
  return lhs >> Lhs(rhs);
}

template <std::derived_from<IInteger> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator>>(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) >> rhs;
}

}
