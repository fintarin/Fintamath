#pragma once

#include "fintamath/core/MathObject.hpp"

namespace fintamath {
  template <typename ObjectType>
  class Comparable : virtual public MathObject<ObjectType> {
  public:
    ~Comparable() override = default;

    virtual bool less(const ObjectType &rhs) const = 0;

    virtual bool more(const ObjectType &rhs) const = 0;

    bool operator<(const ObjectType &rhs) const {
      return less(rhs);
    }

    bool operator>(const ObjectType &rhs) const {
      return more(rhs);
    }

    bool operator<=(const ObjectType &rhs) const {
      return !more(rhs);
    }

    bool operator>=(const ObjectType &rhs) const {
      return !less(rhs);
    }
  };

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return lhs.less(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).less(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return lhs.more(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>(const LhsType &lhs, const RhsType &rhs) {
    return RhsType(lhs).more(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return !lhs.more(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator<=(const LhsType &lhs, const RhsType &rhs) {
    return !RhsType(lhs).more(rhs);
  }

  template <typename LhsType, typename RhsType,
            typename = std::enable_if_t<std::is_base_of_v<Comparable<LhsType>, LhsType> &&
                                        std::is_convertible_v<RhsType, LhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return !lhs.less(LhsType(rhs));
  }

  template <typename RhsType, typename LhsType,
            typename = std::enable_if_t<std::is_base_of_v<MathObjectBase, RhsType> &&
                                        std::is_convertible_v<LhsType, RhsType> && !std::is_same_v<LhsType, RhsType>>>
  bool operator>=(const LhsType &lhs, const RhsType &rhs) {
    return !RhsType(lhs).less(rhs);
  }
}
