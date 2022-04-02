#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename ObjectType>
  class Multipliable : virtual public MathObject<ObjectType> {
  public:
    ~Multipliable() override = default;

    virtual ObjectType &mul(const ObjectType &rhs) = 0;

    virtual ObjectType &div(const ObjectType &rhs) = 0;

    ObjectType &operator*=(const ObjectType &rhs) {
      return mul(rhs);
    }

    ObjectType &operator/=(const ObjectType &rhs) {
      return div(rhs);
    }

    ObjectType operator*(const ObjectType &rhs) const {
      return ObjectType(this->template to<ObjectType>()).mul(rhs);
    }

    ObjectType operator/(const ObjectType &rhs) const {
      return ObjectType(this->template to<ObjectType>()).div(rhs);
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator*=(LhsType &lhs, const RhsType &rhs) {
    return lhs.mul(LhsType(rhs));
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator/=(LhsType &lhs, const RhsType &rhs) {
    return lhs.div(LhsType(rhs));
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return LhsType(lhs).mul(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator*(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).mul(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return LhsType(lhs).div(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Multipliable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator/(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).div(rhs);
  }
}
