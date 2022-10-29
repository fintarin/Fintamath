#pragma once

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/exceptions/FunctionCallException.hpp"
#include "fintamath/helpers/Caster.hpp"

#define FINTAMATH_CALL_OPERATOR(OPER)                                                                                  \
  if (rhs.is<Derived>()) {                                                                                             \
    auto res = (*this OPER rhs.to<Derived>()).simplify();                                                              \
    return helpers::castPtr<IArithmetic>(res);                                                                         \
  }                                                                                                                    \
  if (auto tmp = helpers::convertMathObject(rhs, *this); tmp != nullptr) {                                             \
    auto res = (*this OPER tmp->template to<IArithmetic>())->simplify();                                               \
    return helpers::castPtr<IArithmetic>(res);                                                                         \
  }                                                                                                                    \
  if (auto tmp = helpers::convertMathObject(*this, rhs); tmp != nullptr) {                                             \
    auto res = (tmp->template to<IArithmetic>() OPER rhs)->simplify();                                                 \
    return helpers::castPtr<IArithmetic>(res);                                                                         \
  }                                                                                                                    \
  throw FunctionCallException(#OPER, {toString(), rhs.toString()});

namespace fintamath {
  class IArithmetic;
  using ArithmeticPtr = std::unique_ptr<IArithmetic>;

  class IArithmetic : virtual public IMathObject {
  public:
    ~IArithmetic() override = default;

    friend ArithmeticPtr operator+(const IArithmetic &lhs, const IArithmetic &rhs);

    friend ArithmeticPtr operator-(const IArithmetic &lhs, const IArithmetic &rhs);

    friend ArithmeticPtr operator*(const IArithmetic &lhs, const IArithmetic &rhs);

    friend ArithmeticPtr operator/(const IArithmetic &lhs, const IArithmetic &rhs);

    friend ArithmeticPtr operator+(const IArithmetic &rhs);

    friend ArithmeticPtr operator-(const IArithmetic &rhs);

  protected:
    virtual ArithmeticPtr addAbstract(const IArithmetic &rhs) const = 0;

    virtual ArithmeticPtr substractAbstract(const IArithmetic &rhs) const = 0;

    virtual ArithmeticPtr multiplyAbstract(const IArithmetic &rhs) const = 0;

    virtual ArithmeticPtr divideAbstract(const IArithmetic &rhs) const = 0;

    virtual ArithmeticPtr convertAbstract() const = 0;

    virtual ArithmeticPtr negateAbstract() const = 0;
  };

  inline ArithmeticPtr operator+(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.addAbstract(rhs);
  }

  inline ArithmeticPtr operator-(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.substractAbstract(rhs);
  }

  inline ArithmeticPtr operator*(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.multiplyAbstract(rhs);
  }

  inline ArithmeticPtr operator/(const IArithmetic &lhs, const IArithmetic &rhs) {
    return lhs.divideAbstract(rhs);
  }

  inline ArithmeticPtr operator+(const IArithmetic &rhs) {
    return rhs.convertAbstract();
  }

  inline ArithmeticPtr operator-(const IArithmetic &rhs) {
    return rhs.negateAbstract();
  }

  template <typename Derived>
  class IArithmeticCRTP : virtual public IArithmetic, virtual public IMathObjectCRTP<Derived> {
  public:
    ~IArithmeticCRTP() override = default;

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
      return static_cast<IArithmeticCRTP<Derived> &>(tmp).negate();
    }

  protected:
    virtual Derived &add(const Derived &rhs) = 0;

    virtual Derived &substract(const Derived &rhs) = 0;

    virtual Derived &multiply(const Derived &rhs) = 0;

    virtual Derived &divide(const Derived &rhs) = 0;

    virtual Derived &negate() = 0;

    ArithmeticPtr addAbstract(const IArithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(+);
    }

    ArithmeticPtr substractAbstract(const IArithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(-);
    }

    ArithmeticPtr multiplyAbstract(const IArithmetic &rhs) const final {
      FINTAMATH_CALL_OPERATOR(*);
    }

    ArithmeticPtr divideAbstract(const IArithmetic &rhs) const final {
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
    friend ArithmeticPtr multiDiv(const IArithmetic &lhs, const IArithmetic &rhs);
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
    return lhs += LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
    return lhs -= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs *= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs /= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return lhs + LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) + rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return lhs - LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) - rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return lhs * LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) * rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return lhs / LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<IArithmetic, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) / rhs;
  }
}

#undef FINTAMATH_CALL_OPERATOR
