#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename Derived>
  class Comparable : virtual public MathObjectBase<Derived> {
  public:
    ~Comparable() override = default;

    bool operator<(const Derived &rhs) const {
      return less(rhs);
    }

    bool operator>(const Derived &rhs) const {
      return more(rhs);
    }

    bool operator<=(const Derived &rhs) const {
      return !more(rhs);
    }

    bool operator>=(const Derived &rhs) const {
      return !less(rhs);
    }

  protected:
    virtual bool less(const Derived &rhs) const = 0;

    virtual bool more(const Derived &rhs) const = 0;
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return lhs < LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) < rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return lhs > LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) > rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return lhs <= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) <= rhs;
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return lhs >= LhsType(rhs);
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<RhsType>, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs) >= rhs;
  }
}
