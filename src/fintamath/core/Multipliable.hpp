#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Multipliable : virtual public MathObject {
  public:
    ~Multipliable() override = default;

    friend std::unique_ptr<Multipliable> operator*(const Multipliable &lhs, const Multipliable &rhs);

    friend std::unique_ptr<Multipliable> operator/(const Multipliable &lhs, const Multipliable &rhs);

  protected:
    virtual std::unique_ptr<Multipliable> multiplyAbstract(const Multipliable &rhs) const = 0;

    virtual std::unique_ptr<Multipliable> divideAbstract(const Multipliable &rhs) const = 0;
  };

  inline std::unique_ptr<Multipliable> operator*(const Multipliable &lhs, const Multipliable &rhs) {
    return lhs.multiplyAbstract(rhs);
  }

  inline std::unique_ptr<Multipliable> operator/(const Multipliable &lhs, const Multipliable &rhs) {
    return lhs.divideAbstract(rhs);
  }

  template <typename Derived>
  class MultipliableImpl : virtual public Multipliable, virtual public MathObjectImpl<Derived> {
  public:
    ~MultipliableImpl() override = default;

    Derived &operator*=(const Derived &rhs) {
      return multiply(rhs);
    }

    Derived &operator/=(const Derived &rhs) {
      return divide(rhs);
    }

    Derived operator*(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) *= rhs;
    }

    Derived operator/(const Derived &rhs) const {
      return Derived(static_cast<const Derived &>(*this)) /= rhs;
    }

  protected:
    virtual Derived &multiply(const Derived &rhs) = 0;

    virtual Derived &divide(const Derived &rhs) = 0;

    std::unique_ptr<Multipliable> multiplyAbstract(const Multipliable &rhs) const final {
      if (rhs.is<Derived>()) {
        return std::make_unique<Derived>(*this * rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this * tmp->template to<Multipliable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Multipliable>() * rhs;
      }
      throw std::invalid_argument("Cannot be multiplied");
    }

    std::unique_ptr<Multipliable> divideAbstract(const Multipliable &rhs) const final {
      if (rhs.is<Derived>()) {
        return std::make_unique<Derived>(*this / rhs.to<Derived>());
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this / tmp->template to<Multipliable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Multipliable>() / rhs;
      }
      throw std::invalid_argument("Cannot be divided");
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs *= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs /= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return lhs * LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) * rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return lhs / LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) / rhs;
  }
}
