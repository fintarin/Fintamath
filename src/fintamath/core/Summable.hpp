#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename ObjectType>
  class Summable : virtual public MathObject<ObjectType> {
  public:
    ~Summable() override = default;

    virtual ObjectType &add(const ObjectType &rhs) = 0;

    virtual ObjectType &sub(const ObjectType &rhs) = 0;

    virtual ObjectType &neg() = 0;

    ObjectType &operator+=(const ObjectType &rhs) {
      return add(rhs);
    }

    ObjectType &operator-=(const ObjectType &rhs) {
      return sub(rhs);
    }

    ObjectType operator+(const ObjectType &rhs) const {
      return ObjectType(this->template to<ObjectType>()).add(rhs);
    }

    ObjectType operator-(const ObjectType &rhs) const {
      return ObjectType(this->template to<ObjectType>()).sub(rhs);
    }

    ObjectType operator+() const {
      return ObjectType(this->template to<ObjectType>());
    }

    ObjectType operator-() const {
      return ObjectType(this->template to<ObjectType>()).neg();
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator+=(LhsType &lhs, const RhsType &rhs) {
    return lhs.add(LhsType(rhs));
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType &operator-=(LhsType &lhs, const RhsType &rhs) {
    return lhs.sub(LhsType(rhs));
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return LhsType(lhs).add(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator+(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).add(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  LhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return LhsType(lhs).sub(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Summable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  RhsType operator-(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).sub(rhs);
  }
}
