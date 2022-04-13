#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  class Multipliable : virtual public MathObject {
  public:
    ~Multipliable() override = default;

    virtual std::unique_ptr<Multipliable> operator*(const Multipliable &rhs) const = 0;

    virtual std::unique_ptr<Multipliable> operator/(const Multipliable &rhs) const = 0;
  };

  template <typename Derived>
  class MultipliableImpl : virtual public Multipliable, virtual public MathObjectImpl<Derived> {
  public:
    ~MultipliableImpl() override = default;

    std::unique_ptr<Multipliable> operator*(const Multipliable &rhs) const final {
      if (rhs.is<Derived>()) {
        auto res = std::make_unique<Derived>(to<Derived>());
        *res *= rhs.to<Derived>();
        return res;
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this * tmp->template to<Multipliable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Multipliable>() * rhs;
      }
      throw std::invalid_argument("Cannot be summarized");
    }

    std::unique_ptr<Multipliable> operator/(const Multipliable &rhs) const final {
      if (rhs.is<Derived>()) {
        auto res = std::make_unique<Derived>(to<Derived>());
        *res /= rhs.to<Derived>();
        return res;
      }
      if (auto tmp = meta::convert(*this, rhs); tmp != nullptr) {
        return *this / tmp->template to<Multipliable>();
      }
      if (auto tmp = meta::convert(rhs, *this); tmp != nullptr) {
        return tmp->template to<Multipliable>() / rhs;
      }
      return {};
    }

    Derived &operator*=(const Derived &rhs) {
      return mul(rhs);
    }

    Derived &operator/=(const Derived &rhs) {
      return div(rhs);
    }

    Derived operator*(const Derived &rhs) const {
      std::unique_ptr<MultipliableImpl<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->mul(rhs);
    }

    Derived operator/(const Derived &rhs) const {
      std::unique_ptr<MultipliableImpl<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->div(rhs);
    }

  protected:
    virtual Derived &mul(const Derived &rhs) = 0;

    virtual Derived &div(const Derived &rhs) = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs *= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs /= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return lhs * LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) * rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return lhs / LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MultipliableImpl<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) / rhs;
  }
}
