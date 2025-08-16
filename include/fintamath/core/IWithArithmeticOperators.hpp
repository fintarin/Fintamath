#pragma once

#include "fintamath/core/CoreUtils.hpp"

namespace fintamath {

template <typename Derived>
class IWithArithmeticOperators {
public:
  virtual ~IWithArithmeticOperators() = default;

  friend bool operator==(const Derived &lhs, const Derived &rhs) {
    if (&lhs == &rhs) {
      return true;
    }

    const auto& lhsParent = static_cast<const IWithArithmeticOperators<Derived> &>(lhs);
    return lhsParent.equals(rhs);
  }

  Derived &operator+=(const Derived &rhs) {
    return add(rhs);
  }

  Derived &operator-=(const Derived &rhs) {
    return substract(rhs);
  }

  Derived &operator*=(const Derived &rhs) {
    return multiply(rhs);
  }

  Derived &operator/=(const Derived &rhs) {
    return divide(rhs);
  }

  Derived operator+(const Derived &rhs) const {
    auto lhs = static_cast<const Derived &>(*this);
    return lhs += rhs;
  }

  Derived operator-(const Derived &rhs) const {
    auto lhs = static_cast<const Derived &>(*this);
    return lhs -= rhs;
  }

  Derived operator*(const Derived &rhs) const {
    auto lhs = static_cast<const Derived &>(*this);
    return lhs *= rhs;
  }

  Derived operator/(const Derived &rhs) const {
    auto lhs = static_cast<const Derived &>(*this);
    return lhs /= rhs;
  }

  Derived operator+() const {
    return static_cast<const Derived &>(*this);
  }

  Derived operator-() const {
    auto rhs = static_cast<const Derived &>(*this);
    auto& rhsParent = static_cast<IWithArithmeticOperators<Derived> &>(rhs);
    return rhsParent.negate();
  }

protected:
  virtual bool equals(const Derived &rhs) const = 0;

  virtual Derived &add(const Derived &rhs) = 0;

  virtual Derived &substract(const Derived &rhs) = 0;

  virtual Derived &multiply(const Derived &rhs) = 0;

  virtual Derived &divide(const Derived &rhs) = 0;

  virtual Derived &negate() = 0;
};

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
bool operator==(const Lhs &lhs, const Rhs &rhs) {
  return lhs == Lhs(rhs);
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs &operator+=(Lhs &lhs, const Rhs &rhs) {
  return lhs += Lhs(rhs);
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs &operator-=(Lhs &lhs, const Rhs &rhs) {
  return lhs -= Lhs(rhs);
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs &operator*=(Lhs &lhs, const Rhs &rhs) {
  return lhs *= Lhs(rhs);
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs &operator/=(Lhs &lhs, const Rhs &rhs) {
  return lhs /= Lhs(rhs);
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return lhs + Lhs(rhs);
}

template <typename Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Rhs>, Rhs>)
Rhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) + rhs;
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return lhs - Lhs(rhs);
}

template <typename Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Rhs>, Rhs>)
Rhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) - rhs;
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return lhs * Lhs(rhs);
}

template <typename Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Rhs>, Rhs>)
Rhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) * rhs;
}

template <typename Lhs, ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Lhs>, Lhs>)
Lhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return lhs / Lhs(rhs);
}

template <typename Rhs, ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::is_base_of_v<IWithArithmeticOperators<Rhs>, Rhs>)
Rhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) / rhs;
}

}
