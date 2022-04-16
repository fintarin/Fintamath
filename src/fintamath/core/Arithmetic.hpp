#pragma once

#include "fintamath/core/MathObject.hpp"

#define FINTAMATH_CALL_OPERATOR(OPER)                                                                                  \
  if (rhs.is<Derived>()) {                                                                                             \
    return std::make_unique<Derived>(*this OPER rhs.to<Derived>());                                                    \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(*this, rhs); tmp != nullptr) {                                              \
    return *this OPER tmp->template to<Arithmetic>();                                                                  \
  }                                                                                                                    \
  if (auto tmp = meta::convertRhsToLhsType(rhs, *this); tmp != nullptr) {                                              \
    return tmp->template to<Arithmetic>() OPER rhs;                                                                    \
  }                                                                                                                    \
  throw std::invalid_argument("Incompatible types")

namespace fintamath {
  class Arithmetic;
  using ArithmeticPtr = std::unique_ptr<Arithmetic>;

  class Arithmetic : virtual public MathObject {
  public:
    ~Arithmetic() override = default;

    friend ArithmeticPtr operator+(const Arithmetic &lhs, const Arithmetic &rhs);

    friend ArithmeticPtr operator-(const Arithmetic &lhs, const Arithmetic &rhs);

    friend ArithmeticPtr operator*(const Arithmetic &lhs, const Arithmetic &rhs);

    friend ArithmeticPtr operator/(const Arithmetic &lhs, const Arithmetic &rhs);

    friend ArithmeticPtr operator+(const Arithmetic &rhs);

    friend ArithmeticPtr operator-(const Arithmetic &rhs);

  protected:
    virtual ArithmeticPtr addAbstract(const Arithmetic &rhs) const = 0;

    virtual ArithmeticPtr substractAbstract(const Arithmetic &rhs) const = 0;

    virtual ArithmeticPtr multiplyAbstract(const Arithmetic &rhs) const = 0;

    virtual ArithmeticPtr divideAbstract(const Arithmetic &rhs) const = 0;

    virtual ArithmeticPtr convertAbstract() const = 0;

    virtual ArithmeticPtr negateAbstract() const = 0;
  };

  inline ArithmeticPtr operator+(const Arithmetic &lhs, const Arithmetic &rhs) {
    return lhs.addAbstract(rhs);
  }

  inline ArithmeticPtr operator-(const Arithmetic &lhs, const Arithmetic &rhs) {
    return lhs.substractAbstract(rhs);
  }

  inline ArithmeticPtr operator*(const Arithmetic &lhs, const Arithmetic &rhs) {
    return lhs.multiplyAbstract(rhs);
  }

  inline ArithmeticPtr operator/(const Arithmetic &lhs, const Arithmetic &rhs) {
    return lhs.divideAbstract(rhs);
  }

  inline ArithmeticPtr operator+(const Arithmetic &rhs) {
    return rhs.convertAbstract();
  }

  inline ArithmeticPtr operator-(const Arithmetic &rhs) {
    return rhs.negateAbstract();
  }

  template <typename Derived>
  class ArithmeticImpl : virtual public Arithmetic, virtual public MathObjectImpl<Derived> {
  public:
    ~ArithmeticImpl() override = default;

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
      return Derived(static_cast<const Derived &>(*this)) += rhs;
    }

    Derived operator-(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) -= rhs;
    }

    Derived operator*(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) *= rhs;
    }

    Derived operator/(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) /= rhs;
    }

    Derived operator+() const {
      return Derived(static_cast<const Derived &>(*this));
    }

    Derived operator-() const {
      Derived tmp = Derived(static_cast<const Derived &>(*this));
      return static_cast<ArithmeticImpl<Derived> &>(tmp).negate();
    }

  protected:
    virtual Derived &add(const Derived &rhs) = 0;

    virtual Derived &substract(const Derived &rhs) = 0;

    virtual Derived &multiply(const Derived &rhs) = 0;

    virtual Derived &divide(const Derived &rhs) = 0;

    virtual Derived &negate() = 0;

    ArithmeticPtr addAbstract(const Arithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(+);
    }

    ArithmeticPtr substractAbstract(const Arithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(-);
    }

    ArithmeticPtr multiplyAbstract(const Arithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(*);
    }

    ArithmeticPtr divideAbstract(const Arithmetic &rhs) const final {
      if (auto tmp = multiDiv(*this, rhs); tmp != nullptr) {
        return tmp;
      }
      FINTAMATH_CALL_OPERATOR(/);
    }

    ArithmeticPtr convertAbstract() const final {
      return std::make_unique<Derived>(+(*this));
    }

    ArithmeticPtr negateAbstract() const final {
      return std::make_unique<Derived>(-(*this));
    }

  private:
    friend ArithmeticPtr multiDiv(const Arithmetic &lhs ,const Arithmetic &rhs);
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
    return lhs += LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
    return lhs -= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs *= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs /= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return lhs + LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) + rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return lhs - LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) - rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return lhs * LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) * rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return lhs / LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Arithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) / rhs;
  }
}

#undef FINTAMATH_CALL_OPERATOR
