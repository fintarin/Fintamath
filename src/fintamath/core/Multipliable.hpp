#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename Derived>
  class Multipliable : virtual public MathObjectImpl<Derived> {
  public:
    ~Multipliable() override = default;

    Derived &operator*=(const Derived &rhs) {
      return mul(rhs);
    }

    Derived &operator/=(const Derived &rhs) {
      return div(rhs);
    }

    Derived operator*(const Derived &rhs) const {
      std::unique_ptr<Multipliable<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->mul(rhs);
    }

    Derived operator/(const Derived &rhs) const {
      std::unique_ptr<Multipliable<Derived>> tmp = std::make_unique<Derived>(this->template to<Derived>());
      return tmp->div(rhs);
    }

  protected:
    virtual Derived &mul(const Derived &rhs) = 0;

    virtual Derived &div(const Derived &rhs) = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs *= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs /= LhsType(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return lhs * LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) * rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return lhs / LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) / rhs;
  }
}
