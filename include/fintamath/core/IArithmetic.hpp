#pragma once

#include <concepts>
#include <memory>
#include <string>
#include <utility>

#include "fintamath/core/CoreUtils.hpp"
#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectType.hpp"
#include "fintamath/core/Parser.hpp"

namespace fintamath {

class IArithmetic : public IMathObject {
  using ArithmeticParser = detail::Parser<std::unique_ptr<IArithmetic>()>;

public:
  friend std::unique_ptr<IArithmetic> operator+(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.addAbstract(rhs);
  }

  friend std::unique_ptr<IArithmetic> operator-(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.substractAbstract(rhs);
  }

  friend std::unique_ptr<IArithmetic> operator*(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.multiplyAbstract(rhs);
  }

  friend std::unique_ptr<IArithmetic> operator/(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.divideAbstract(rhs);
  }

  friend std::unique_ptr<IArithmetic> operator+(const IArithmetic &rhs) {
    return cast<IArithmetic>(rhs.clone());
  }

  friend std::unique_ptr<IArithmetic> operator-(const IArithmetic &rhs) {
    return rhs.negateAbstract();
  }

  static std::unique_ptr<IArithmetic> parse(const std::string &str) {
    return getParser().parse(str);
  }

  template <std::derived_from<IArithmetic> T>
  static void registerType() {
    getParser().registerType<T>();
  }

  static void registerType(ArithmeticParser::StringConstructor constructor) {
    getParser().registerType(std::move(constructor));
  }

  static constexpr MathObjectType getTypeStatic() {
    return {MathObjectType::IArithmetic, "IArithmetic"};
  }

protected:
  virtual std::unique_ptr<IArithmetic> addAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> substractAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> multiplyAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> divideAbstract(const IArithmetic &rhs) const = 0;

  virtual std::unique_ptr<IArithmetic> negateAbstract() const = 0;

private:
  static ArithmeticParser &getParser();
};

template <typename Derived>
class IArithmeticCRTP : public IArithmetic {
#define I_ARITHMETIC_CRTP IArithmeticCRTP<Derived>
#include "fintamath/core/IArithmeticCRTP.hpp"
#undef I_ARITHMETIC_CRTP
};

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator+=(Lhs &lhs, const Rhs &rhs) {
  return lhs += Lhs(rhs);
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator-=(Lhs &lhs, const Rhs &rhs) {
  return lhs -= Lhs(rhs);
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator*=(Lhs &lhs, const Rhs &rhs) {
  return lhs *= Lhs(rhs);
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs &operator/=(Lhs &lhs, const Rhs &rhs) {
  return lhs /= Lhs(rhs);
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return lhs + Lhs(rhs);
}

template <std::derived_from<IArithmetic> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) + rhs;
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return lhs - Lhs(rhs);
}

template <std::derived_from<IArithmetic> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) - rhs;
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return lhs * Lhs(rhs);
}

template <std::derived_from<IArithmetic> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) * rhs;
}

template <std::derived_from<IArithmetic> Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
Lhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return lhs / Lhs(rhs);
}

template <std::derived_from<IArithmetic> Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
Rhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) / rhs;
}

}
