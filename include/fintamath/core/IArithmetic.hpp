#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/InvalidInputException.hpp"

namespace fintamath {

class IArithmetic : public IMathObject {
  using ArithmeticParser = Parser<std::unique_ptr<IArithmetic>>;

public:
  friend inline std::unique_ptr<IArithmetic> operator+(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.addAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator-(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.substractAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator*(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.multiplyAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator/(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.divideAbstract(rhs);
  }

  friend inline std::unique_ptr<IArithmetic> operator+(const IArithmetic &rhs) {
    return cast<IArithmetic>(rhs.clone());
  }

  friend inline std::unique_ptr<IArithmetic> operator-(const IArithmetic &rhs) {
    return rhs.negateAbstract();
  }

  static std::unique_ptr<IArithmetic> parse(const std::string &str) {
    return getParser().parse(str);
  }

  template <std::derived_from<IArithmetic> T>
  static void registerConstructor() {
    getParser().registerConstructor<T>();
  }

  static void registerConstructor(ArithmeticParser::Constructor constructor) {
    getParser().registerConstructor(std::move(constructor));
  }

  static MathObjectType getTypeStatic() {
    return MathObjectType::IArithmetic;
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
