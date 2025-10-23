#pragma once

#include "fintamath/core/CoreUtils.hpp"

namespace fintamath {

template <typename Derived>
class IWithArithmeticOperators {
public:
  virtual ~IWithArithmeticOperators() = default;

  Derived &operator+=(const Derived &rhs) {
    return add(rhs);
  }

  Derived &operator-=(const Derived &rhs) {
    return sub(rhs);
  }

  Derived &operator*=(const Derived &rhs) {
    return mul(rhs);
  }

  Derived &operator/=(const Derived &rhs) {
    return div(rhs);
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
    auto &rhsParent = static_cast<IWithArithmeticOperators<Derived> &>(rhs);
    return rhsParent.neg();
  }

protected:
  virtual Derived &add(const Derived &rhs) = 0;

  virtual Derived &sub(const Derived &rhs) = 0;

  virtual Derived &mul(const Derived &rhs) = 0;

  virtual Derived &div(const Derived &rhs) = 0;

  virtual Derived &neg() = 0;
};

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs &operator+=(Lhs &lhs, const Rhs &rhs) {
  return lhs += Lhs(rhs);
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs &operator-=(Lhs &lhs, const Rhs &rhs) {
  return lhs -= Lhs(rhs);
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs &operator*=(Lhs &lhs, const Rhs &rhs) {
  return lhs *= Lhs(rhs);
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs &operator/=(Lhs &lhs, const Rhs &rhs) {
  return lhs /= Lhs(rhs);
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return lhs + Lhs(rhs);
}

template <typename Rhs, detail::ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::derived_from<Rhs, IWithArithmeticOperators<Rhs>>)
Rhs operator+(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) + rhs;
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return lhs - Lhs(rhs);
}

template <typename Rhs, detail::ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::derived_from<Rhs, IWithArithmeticOperators<Rhs>>)
Rhs operator-(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) - rhs;
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return lhs * Lhs(rhs);
}

template <typename Rhs, detail::ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::derived_from<Rhs, IWithArithmeticOperators<Rhs>>)
Rhs operator*(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) * rhs;
}

template <typename Lhs, detail::ConvertibleToAndNotSameAs<Lhs> Rhs>
  requires(std::derived_from<Lhs, IWithArithmeticOperators<Lhs>>)
Lhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return lhs / Lhs(rhs);
}

template <typename Rhs, detail::ConvertibleToAndNotSameAs<Rhs> Lhs>
  requires(std::derived_from<Rhs, IWithArithmeticOperators<Rhs>>)
Rhs operator/(const Lhs &lhs, const Rhs &rhs) {
  return Rhs(lhs) / rhs;
}

}
